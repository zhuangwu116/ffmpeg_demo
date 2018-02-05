#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <SDL/SDL.h>
#include <SDL/SDL_thread.h>

#include <stdio.h>
#ifdef __MINGW32__
#undef main
#endif

#if LIBAVCODEC_VERSION_INT < AV_VERSION_INT(55,28,1)
#define av_frame_alloc avcodec_alloc_frame
#define av_frame_free avcodec_free_frame
#endif

/*void SaveFrame(AVFrame* pFrame, int width, int height, int iFrame){
    FILE* pFile;
    char szFilename[32];
    int y;

    sprintf(szFilename, "frame%d.ppm", iFrame);
    pFile = fopen(szFilename, "wb");

    if(pFile == NULL)
        return;

    fprintf(pFile, "P6\n%d %d\n\n255\n", width, height);

    for(y=0; y < height; y++)
        fwrite(pFrame->data[0]+y*pFrame->linesize[0], 1, width*3, pFile);

    fclose(pFile);
}*/



int main(int argc, char* argv[]){
    AVFormatContext *pFormatCtx = NULL;
    int             i, videoStream;
    AVCodecContext  *pCodecCtxOrig = NULL;
    AVCodecContext  *pCodecCtx = NULL;
    AVCodec         *pCodec = NULL;
    AVFrame         *pFrame = NULL;
    AVFrame         *pFrameRGB = NULL;
    AVPacket        packet;
    int             frameFinished;
    int             numBytes;
    uint8_t         *buffer = NULL;
    struct SwsContext *sws_ctx = NULL;



    SDL_Overlay *bmp;
    SDL_Surface *screen;
    SDL_Rect rect;
    SDL_Event event;

    if(argc < 2)
    {
        fprintf(stderr,"Usage: test <file>\n");
        return -1;
    }

    av_register_all();

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)){
        fprintf(stderr,"Could not initialize SDL - %s\n", SDL_GetError());
        exit(1);
    }


    if(avformat_open_input(&pFormatCtx,argv[1],NULL,NULL)!=0)
        return -1;

    if(avformat_find_stream_info(pFormatCtx,NULL) < 0)
        return -1;

    av_dump_format(pFormatCtx,0,argv[1], 0);

    videoStream = -1;
    for(i=0;i<pFormatCtx->nb_streams; i++)
        if(pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO){
            videoStream=i;
            break;
        }
    if(videoStream==-1)
        return -1;

    pCodecCtxOrig = pFormatCtx->streams[videoStream]->codec;
    pCodec = avcodec_find_decoder(pCodecCtxOrig->codec_id);
    if(pCodec==NULL){
        fprintf(stderr,"Unsupported codec!\n");
        return -1;
    }
    pCodecCtx = avcodec_alloc_context3(pCodec);

    if(avcodec_copy_context(pCodecCtx,pCodecCtxOrig)!=0){
        fprintf(stderr,"Couldn't copy codec context");
        return -1;
    }

    if(avcodec_open2(pCodecCtx, pCodec, NULL)<0)
        return -1;

    pFrame = av_frame_alloc();

#ifndef __DARWIN__
    screen = SDL_SetVideoMode(pCodecCtx->width, pCodecCtx->height, 0, 0);
#else
    screen = SDL_SetVideoMode(pCodecCtx->width,pCodecCtx->height, 24, 0);
#endif
    if(!screen){
        fprintf(stderr,"SDL: could not set video mode - exiting\n");
        exit(1);
    }

    bmp = SDL_CreateYUVOverlay(pCodecCtx->width,pCodecCtx->height,SDL_YV12_OVERLAY,screen);

    /*pFrameRGB = av_frame_alloc();

    if(pFrameRGB == NULL)
        return -1;

    numBytes = avpicture_get_size(PIX_FMT_RGB24, pCodecCtx->width,
            pCodecCtx->height);

    buffer = (uint8_t*)av_malloc(numBytes*sizeof(uint8_t));

    avpicture_fill((AVPicture*)pFrameRGB, buffer, PIX_FMT_RGB24,
            pCodecCtx->width,pCodecCtx->height);*/


    /*sws_ctx = sws_getContext(pCodecCtx->width,pCodecCtx->height,
            pCodecCtx->pix_fmt,pCodecCtx->width,pCodecCtx->height,
            PIX_FMT_RGB24,SWS_BILINEAR,NULL,NULL,NULL);*/
    sws_ctx = sws_getContext(pCodecCtx->width,pCodecCtx->height,
            pCodecCtx->pix_fmt,pCodecCtx->width,pCodecCtx->height,
            PIX_FMT_YUV420P,SWS_BILINEAR,NULL,NULL,NULL);
    i = 0;
    while(av_read_frame(pFormatCtx,&packet)>=0){
        if(packet.stream_index == videoStream){
            avcodec_decode_video2(pCodecCtx,pFrame,&frameFinished,&packet);
            if(frameFinished){
                SDL_LockYUVOverlay(bmp);

                AVPicture pict;

                pict.data[0] = bmp->pixels[0];
                pict.data[1] = bmp->pixels[2];
                pict.data[2] = bmp->pixels[1];

                pict.linesize[0] = bmp->pitches[0];
                pict.linesize[1] = bmp->pitches[2];
                pict.linesize[2] = bmp->pitches[1];



                /*sws_scale(sws_ctx,(uint8_t const * const *)pFrame->data,
                /*        pFrame->linesize,0,pCodecCtx->height,
                /*        pFrameRGB->data,pFrameRGB->linesize);*/

                sws_scale(sws_ctx,(uint8_t const * const *)pFrame->data,
                        pFrame->linesize,0,pCodecCtx->height,
                        pict.data,pict.linesize);

                SDL_UnlockYUVOverlay(bmp);

                rect.x = 0;
                rect.y = 0;
                rect.w = pCodecCtx->width;
                rect.h = pCodecCtx->height;
                SDL_DisplayYUVOverlay(bmp,&rect);
                /*
                if(++i<=5)
                    SaveFrame(pFrameRGB,pCodecCtx->width,pCodecCtx->height,i);*/
            }
        }
        av_free_packet(&packet);
        SDL_PollEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                SDL_Quit();
                exit(0);
                break;
            default:
                break;
        }
    }
    //av_free(buffer);
    //av_frame_free(&pFrameRGB);

    av_frame_free(&pFrame);

    avcodec_close(pCodecCtx);
    avcodec_close(pCodecCtxOrig);

    avformat_close_input(&pFormatCtx);

    return 0;


    
}

