#ifndef vectorstatistiche_h
#define vectorstatistiche_h

#include <vector>
#include <cmath>

template <typename T>
float sampleMean(std::vector<T> sample)
{
    float sum = 0.0;

    for(int i = 0; i < sample.size(); ++i)
    {
        sum += sample.at(i);
    }

    return sum / (sample.size());
}

template <typename T>
float sampleVariance(std::vector<T> sample, bool bessel)
{
    float sumsq = 0.0;
    float media = sampleMean(sample);

    for(int i = 0; i < sample.size(); ++i) 
    {
        sumsq += pow((sample[i] - media), 2);
    }

    if(!bessel)
    {
        return sumsq / (sample.size());
    }

    else   
    {
        return sumsq / (sample.size() - 1);
    }    
}

template <typename T>
float sampleStd(std::vector<T> sample, bool bessel)
{
    float varianza = sampleVariance(sample, bessel);
    return sqrt(varianza);
}

template <typename T>
float sampleSkewness(std::vector<T> sample, bool bessel)
{
    float media = sampleMean(sample);
    float std = sampleStd(sample, bessel);
    float skw = 0.0;

    for(int i = 0; i < sample.size(); ++i)
    {
        skw += pow((sample.at(i) - media), 3);
    }

    return skw / (sample.size() * pow(std, 3));
}

template <typename T>
float sampleKurtosis(std::vector<T> sample, bool bessel)
{
    float media = sampleMean(sample);
    float varianza = sampleVariance(sample, bessel);
    float kur = 0.0;

    for(int i = 0; i < sample.size(); ++i)
    {
        kur += pow((sample.at(i) - media), 4);
    }

    return kur / (sample.size() * pow(varianza, 2)) - 3.0;
}

#endif