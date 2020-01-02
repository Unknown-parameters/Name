int IM_BacklightRepair(unsigned char *Src, unsigned char *Dest, int Width, int Height, int Stride)
{
    int Channel = Stride / Width;
    if (Channel != 3)                                    return IM_STATUS_INVALIDPARAMETER;
    if ((Src == NULL) || (Dest == NULL))                return IM_STATUS_NULLREFRENCE;
    if ((Width <= 0) || (Height <= 0))                    return IM_STATUS_INVALIDPARAMETER;

    int Status = IM_STATUS_OK;
    int RadiusS = 5, RadiusM = 20, RadiusL = 120;
    const int LowLevel = 50, HighLevel = 150;
    const float MinCDF = 0.1f;

    int *Histgram = (int *)calloc(256, sizeof(int));
    unsigned char *Table = (unsigned char *)malloc(256 * 256 * sizeof(unsigned char));        //    各尺度的模糊
    unsigned char *BlurS = (unsigned char *)malloc(Width * Height * sizeof(unsigned char));        //    各尺度的模糊
    unsigned char *BlurM = (unsigned char *)malloc(Width * Height * sizeof(unsigned char));
    unsigned char *BlurL = (unsigned char *)malloc(Width * Height * sizeof(unsigned char));
    unsigned char *Luminance = (unsigned char *)malloc(Width * Height * sizeof(unsigned char));
    if ((Histgram == NULL) || (Table == NULL) || (BlurS == NULL) || (BlurM == NULL) || (BlurL == NULL) || (Luminance == NULL))
    {
        Status = IM_STATUS_OUTOFMEMORY;
        goto FreeMemory;
    }

    float Z = 0, P = 0;
    Status = IM_GetLuminance(Src, Luminance, Width, Height, Stride, false);            //    得到亮度分量
    if (Status != IM_STATUS_OK)    goto FreeMemory;

    for (int Y = 0; Y < Height * Width; Y++)        Histgram[Luminance[Y]]++;        //    统计亮度分量的直方图

    float Sum = 0, Mean = 0, StdDev = 0;
    for (int Y = 0; Y < 256; Y++)                    Sum += Histgram[Y] * Y;            //    像素的总和，注意用float类型保存
    Mean = Sum / (Width * Height);                                                    //    平均值
    for (int Y = 0; Y < 256; Y++)                    StdDev += Histgram[Y] * (Y - Mean) * (Y - Mean);
    StdDev = sqrtf(StdDev / (Width * Height));                                        //    全局图像的均方差

    int CDF = 0, L = 0;
    for (L = 0; L < 256; L++)
    {
        CDF += Histgram[L];
        if (CDF >= Width * Height * MinCDF)        break;    //    where L is the intensity level corresponding to a cumulative distribution function CDF of 0.1.
    }
    if (L <= LowLevel)
        Z = 0;
    else if (L <= HighLevel)
        Z = (L - LowLevel) * 1.0f / (HighLevel - LowLevel);                            //    计算Z值
    else
        Z = 1;

    if (StdDev <= 3)                                    //    计算P值，Also, P is determined by the globaln standard deviation  of the input intensity image Ix, y as
        P = 3;
    else if (StdDev <= 10)
        P = (27 - 2 * StdDev) / 7.0f;
    else
        P = 1;

    for (int Y = 0; Y < 256; Y++)                    //    Y表示的是I的卷积值
    {
        for (int X = 0; X < 256; X++)                //    X表示的I(原始亮度值)
        {
            float I = X * IM_INV255;                                                                        //    公式2
            I = (powf(I, 0.75f * Z + 0.25f) + (1 - I) * 0.4f * (1 - Z) + powf(I, 2 - Z)) * 0.5f;            //    公式3
            Table[Y * 256 + X] = IM_ClampToByte(255 * powf(I, powf((Y + 1.0f) / (X + 1.0f), P)) + 0.5f);    //    公式7及8
        }
    }

    Status = IM_GaussBlur(Luminance, BlurS, Width, Height, Width, RadiusS);
    if (Status != IM_STATUS_OK)    goto FreeMemory;
    Status = IM_GaussBlur(Luminance, BlurM, Width, Height, Width, RadiusM);
    if (Status != IM_STATUS_OK)    goto FreeMemory;
    Status = IM_GaussBlur(Luminance, BlurL, Width, Height, Width, RadiusL);
    if (Status != IM_STATUS_OK)    goto FreeMemory;

    for (int Y = 0; Y < Height; Y++)
    {
        unsigned char *LinePS = Src + Y * Stride;
        unsigned char *LinePD = Dest + Y * Stride;
        int Index = Y * Width;
        for (int X = 0; X < Width; X++, Index++, LinePS += 3, LinePD += 3)
        {
            int L = Luminance[Index];
            if (L == 0)
            {
                LinePD[0] = 0;    LinePD[1] = 0;    LinePD[2] = 0;
            }
            else
            {
                int Value = ((Table[L + (BlurS[Index] << 8)] + Table[L + (BlurM[Index] << 8)] + Table[L + (BlurL[Index] << 8)]) / 3);        //    公式13
                LinePD[0] = IM_ClampToByte(LinePS[0] * Value / L);
                LinePD[1] = IM_ClampToByte(LinePS[1] * Value / L);
                LinePD[2] = IM_ClampToByte(LinePS[2] * Value / L);
            }
        }
    }

FreeMemory:
    if (Histgram != NULL)    free(Histgram);
    if (Table != NULL)        free(Table);
    if (BlurS != NULL)        free(BlurS);
    if (BlurM != NULL)        free(BlurM);
    if (BlurL != NULL)        free(BlurL);
    if (Luminance != NULL)    free(Luminance);
}