
class Model(dygraph.layers.Layer):
    def __init__(self, name_scope, use_poster, use_mov_title, use_mov_cat, use_age_job):
        super(Model, self).__init__(name_scope)
        name = self.full_name()
        
        # 将传入的name信息和bool型参数添加到模型类中
        self.use_mov_poster = use_poster
        self.use_mov_title = use_mov_title
        self.use_usr_age_job = use_age_job
        self.use_mov_cat = use_mov_cat
        
        # 获取数据集的信息，并构建训练和验证集的数据迭代器
        Dataset = MovieLen(self.use_mov_poster)
        self.Dataset = Dataset
        self.trainset = self.Dataset.train_dataset
        self.valset = self.Dataset.valid_dataset
        self.train_loader = self.Dataset.load_data(dataset=self.trainset, mode='train')
        self.valid_loader = self.Dataset.load_data(dataset=self.valset, mode='valid')

        """ define network layer for embedding usr info """
        USR_ID_NUM = Dataset.max_usr_id + 1
        # 对用户ID做映射，并紧接着一个FC层
        self.usr_emb = Embedding([USR_ID_NUM, 32], is_sparse=False)
        self.usr_fc = Linear(32, 32)
        
        # 对用户性别信息做映射，并紧接着一个FC层
        USR_GENDER_DICT_SIZE = 2
        self.usr_gender_emb = Embedding([USR_GENDER_DICT_SIZE, 16])
        self.usr_gender_fc = Linear(16, 16)
        
        # 对用户年龄信息做映射，并紧接着一个FC层
        USR_AGE_DICT_SIZE = Dataset.max_usr_age + 1
        self.usr_age_emb = Embedding([USR_AGE_DICT_SIZE, 16])
        self.usr_age_fc = Linear(16, 16)
        
        # 对用户职业信息做映射，并紧接着一个FC层
        USR_JOB_DICT_SIZE = Dataset.max_usr_job + 1
        self.usr_job_emb = Embedding([USR_JOB_DICT_SIZE, 16])
        self.usr_job_fc = Linear(16, 16)
        
        # 新建一个FC层，用于整合用户数据信息
        self.usr_combined = Linear(80, 200, act='tanh')
        
        """ define network layer for embedding usr info """
        # 对电影ID信息做映射，并紧接着一个FC层
        MOV_DICT_SIZE = Dataset.max_mov_id + 1
        self.mov_emb = Embedding([MOV_DICT_SIZE, 32])
        self.mov_fc = Linear(32, 32)
        
        # 对电影类别做映射
        CATEGORY_DICT_SIZE = len(Dataset.movie_cat) + 1
        self.mov_cat_emb = Embedding([CATEGORY_DICT_SIZE, 32], is_sparse=False)
        self.mov_cat_fc = Linear(32, 32)
        
        # 对电影名称做映射
        MOV_TITLE_DICT_SIZE = len(Dataset.movie_title) + 1
        self.mov_title_emb = Embedding([MOV_TITLE_DICT_SIZE, 32], is_sparse=False)
        self.mov_title_conv = Conv2D(1, 1, filter_size=(3, 1), stride=(2,1), padding=0, act='relu')
        self.mov_title_conv2 = Conv2D(1, 1, filter_size=(3, 1), stride=1, padding=0, act='relu')
        
        # 新建一个FC层，用于整合电影特征
        self.mov_concat_embed = Linear(96, 200, act='tanh')
        
    # 定义计算用户特征的前向运算过程
    def get_usr_feat(self, usr_var):
        """ get usr features"""
        # 获取到用户数据
        usr_id, usr_gender, usr_age, usr_job = usr_var
        # 将用户的ID数据经过embedding和FC计算，得到的特征保存在feats_collect中
        feats_collect = []
        usr_id = self.usr_emb(usr_id)
        usr_id = self.usr_fc(usr_id)
        usr_id = fluid.layers.relu(usr_id)
        feats_collect.append(usr_id)
        
        # 计算用户的性别特征，并保存在feats_collect中
        usr_gender = self.usr_gender_emb(usr_gender)
        usr_gender = self.usr_gender_fc(usr_gender)
        usr_gender = fluid.layers.relu(usr_gender)
        feats_collect.append(usr_gender)
        # 选择是否使用用户的年龄-职业特征
        if self.use_usr_age_job:
            # 计算用户的年龄特征，并保存在feats_collect中
            usr_age = self.usr_age_emb(usr_age)
            usr_age = self.usr_age_fc(usr_age)
            usr_age = fluid.layers.relu(usr_age)
            feats_collect.append(usr_age)
            # 计算用户的职业特征，并保存在feats_collect中
            usr_job = self.usr_job_emb(usr_job)
            usr_job = self.usr_job_fc(usr_job)
            usr_job = fluid.layers.relu(usr_job)
            feats_collect.append(usr_job)
        
        # 将用户的特征级联，并通过FC层得到最终的用户特征
        usr_feat = fluid.layers.concat(feats_collect, axis=1)
        usr_feat = self.usr_combined(usr_feat)
        return usr_feat

        # 定义电影特征的前向计算过程
    def get_mov_feat(self, mov_var):
        """ get movie features"""
        # 获得电影数据
        mov_id, mov_cat, mov_title, mov_poster = mov_var
        feats_collect = []
        # 获得batchsize的大小
        batch_size = mov_id.shape[0]
        # 计算电影ID的特征，并存在feats_collect中
        mov_id = self.mov_emb(mov_id)
        mov_id = self.mov_fc(mov_id)
        mov_id = fluid.layers.relu(mov_id)
        feats_collect.append(mov_id)
        
        # 如果使用电影的种类数据，计算电影种类特征的映射
        if self.use_mov_cat:
            # 计算电影种类的特征映射，对多个种类的特征求和得到最终特征
            mov_cat = self.mov_cat_emb(mov_cat)
            mov_cat = fluid.layers.reduce_sum(mov_cat, dim=1, keep_dim=False)

            mov_cat = self.mov_cat_fc(mov_cat)
            feats_collect.append(mov_cat)

        if self.use_mov_title:
            # 计算电影名字的特征映射，对特征映射使用卷积计算最终的特征
            mov_title = self.mov_title_emb(mov_title)
            mov_title = self.mov_title_conv2(self.mov_title_conv(mov_title))
            mov_title = fluid.layers.reduce_sum(mov_title, dim=2, keep_dim=False)
            mov_title = fluid.layers.relu(mov_title)
            mov_title = fluid.layers.reshape(mov_title, [batch_size, -1])
            feats_collect.append(mov_title)
            
        # 使用一个全连接层，整合所有电影特征，映射为一个200维的特征向量
        mov_feat = fluid.layers.concat(feats_collect, axis=1)
        mov_feat = self.mov_concat_embed(mov_feat)
        return mov_feat
    
    # 定义个性化推荐算法的前向计算
    def forward(self, usr_var, mov_var):
        # 计算用户特征和电影特征
        usr_feat = self.get_usr_feat(usr_var)
        mov_feat = self.get_mov_feat(mov_var)
        # 根据计算的特征计算相似度
        res = fluid.layers.cos_sim(usr_feat, mov_feat)
        # 将相似度扩大范围到和电影评分相同数据范围
        res = fluid.layers.scale(res, scale=5)
        return usr_feat, mov_feat, res
   