#include <filesystem>
#include <iostream>
#include <string>

#include "SDL2/SDL.h"
extern "C" {
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
}

int main(int argc, char *argv[]) {
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_EVENTS);

  // Load Video File
  std::string mp4_filename = argc > 1 ? argv[1] : "../demo/trailer.mp4";
  mp4_filename = std::filesystem::absolute(mp4_filename);
  AVFormatContext *format = NULL;
  avformat_open_input(&format, mp4_filename.c_str(), NULL, NULL);
  int vi = av_find_best_stream(format, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
  int ai = av_find_best_stream(format, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0);
  double frame_duration = av_q2d(format->streams[vi]->time_base) * 1000;
  int frame_width = format->streams[vi]->codecpar->width;
  int frame_height = format->streams[vi]->codecpar->height;
  int sample_rate = format->streams[ai]->codecpar->sample_rate;
  int channels = format->streams[ai]->codecpar->ch_layout.nb_channels;
  std::cout << "Video Stream Index: " << vi << std::endl;
  std::cout << "Audio Stream Index: " << ai << std::endl;
  std::cout << "FPS: " << 1000 / frame_duration << std::endl;
  std::cout << "Width: " << frame_width << std::endl;
  std::cout << "Height: " << frame_height << std::endl;
  std::cout << "Sample Rate: " << sample_rate << std::endl;
  std::cout << "Channels: " << channels << std::endl;

  // Initialize Video Decoder
  AVCodecParameters *params = format->streams[vi]->codecpar;
  const AVCodec *v_codec = avcodec_find_decoder(params->codec_id);
  AVCodecContext *v_context = avcodec_alloc_context3(v_codec);
  avcodec_parameters_to_context(v_context, params);
  avcodec_open2(v_context, v_codec, NULL);

  // Initialize Audio Decoder
  params = format->streams[ai]->codecpar;
  const AVCodec *a_codec = avcodec_find_decoder(params->codec_id);
  AVCodecContext *a_context = avcodec_alloc_context3(a_codec);
  avcodec_parameters_to_context(a_context, params);
  avcodec_open2(a_context, a_codec, NULL);

  // Initialize Window
  SDL_Window *window = SDL_CreateWindow(
      mp4_filename.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      frame_width, frame_height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
  SDL_Texture *texture =
      SDL_CreateTexture(renderer, SDL_PIXELFORMAT_IYUV,
                        SDL_TEXTUREACCESS_STREAMING, frame_width, frame_height);
  SDL_Rect rect = {.x = 0, .y = 0, .w = frame_width, .h = frame_height};

  // Initialize Audio Device
  SDL_AudioSpec wanted_spec, spec;
  SDL_memset(&wanted_spec, 0, sizeof(wanted_spec));
  wanted_spec.freq = a_context->sample_rate;
  wanted_spec.format = AUDIO_S16SYS;
  wanted_spec.channels = a_context->ch_layout.nb_channels;
  wanted_spec.silence = 0;
  wanted_spec.samples = 1024;
  SDL_AudioDeviceID device =
      SDL_OpenAudioDevice(NULL, 0, &wanted_spec, &spec, 0);
  SDL_PauseAudioDevice(device, 0);

  // Play Video
  SDL_Event event;
  AVPacket packet;
  AVFrame *frame = av_frame_alloc();
  Uint32 start_time = SDL_GetTicks();
  while (av_read_frame(format, &packet) == 0) {
    if (packet.stream_index == vi) {
      avcodec_send_packet(v_context, &packet);
      avcodec_receive_frame(v_context, frame);
      SDL_UpdateYUVTexture(texture, NULL, frame->data[0], frame->linesize[0],
                           frame->data[1], frame->linesize[1], frame->data[2],
                           frame->linesize[2]);
      SDL_RenderClear(renderer);
      SDL_RenderCopy(renderer, texture, NULL, &rect);
      SDL_RenderPresent(renderer);
      Uint32 current_time = SDL_GetTicks();
      Uint32 frame_time = current_time - start_time;
      if (frame_time < frame_duration)
        SDL_Delay((Uint32)(frame_duration - frame_time));
      SDL_Delay((Uint32)(frame_duration));
      start_time = SDL_GetTicks();
    } else if (packet.stream_index == ai) {
      avcodec_send_packet(a_context, &packet);
      avcodec_receive_frame(a_context, frame);
      SDL_QueueAudio(device, frame->data[0], frame->linesize[0]);
    }
    av_packet_unref(&packet);
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT)
      break;
  }

  // Clean Up
  av_frame_free(&frame);
  avcodec_free_context(&a_context);
  avcodec_free_context(&v_context);
  avformat_close_input(&format);
  SDL_CloseAudioDevice(device);
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}