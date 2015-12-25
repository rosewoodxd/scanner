#pragma once

#include <vector>
#include <cstdint>
#include <memory>
#include <thread>

class SampleBuffer;

class SignalSource
{
 protected:
  bool m_doTiming;
  struct timespec m_start, m_stop;
  double m_elapsedTime;
  uint32_t m_retuneTimeIndex;
  uint32_t m_getSamplesTimeIndex;
  bool m_finished;
  std::unique_ptr<std::thread> m_thread;
  std::vector<double> m_retuneTime;
  std::vector<double> m_getSamplesTime;
  static const uint32_t s_maxIndex = 10000;

 protected:
  uint32_t m_sampleRate;
  uint32_t m_sampleCount;
  double m_startFrequency;
  double m_stopFrequency;
  std::vector<double> m_frequencies;
  uint32_t m_frequencyIndex;
  uint32_t m_iterationCount;
  SampleBuffer * m_sampleBuffer;
  bool StopThread();
  bool StartThread();
  void ThreadWorkerHelper();
  uint32_t GetIterationCount();
  double GetCurrentFrequency();
  double GetNextFrequency();
  uint32_t GetFrequencyCount();
  
 public:
  SignalSource(uint32_t m_sampleRate,
               uint32_t m_sampleCount,
               double m_startFrequency,
               double m_stopFrequency,
               bool doTiming = false);
  virtual ~SignalSource();
  virtual bool Start();
  virtual bool GetNextSamples(SampleBuffer * sample_buffer, double_t & centerFrequency) = 0;
  virtual bool StartStreaming(uint32_t numIterations, SampleBuffer & sampleBuffer) = 0;
  virtual void ThreadWorker() = 0;
  virtual bool Stop();
  virtual double Retune(double frequency) = 0;
  void StopStreaming();
  void StartTimer();
  void StopTimer();
  void AddRetuneTime();
  void AddGetSamplesTime();
  void WriteTimingData();
};
