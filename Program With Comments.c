#include <stdio.h>
#include <stdlib.h>
#include <alsa/asoundlib.h>
#include <math.h>
#include <time.h>

main (int argc, char *argv[])
{
int i;
int err;
char *buffer;
int buffer_frames = 128;
unsigned int rate = 44100;
 snd_pcm_t *capture_handle;
snd_pcm_hw_params_t *hw_params;
snd_pcm_format_t format = SND_PCM_FORMAT_S16_LE;
Int Frequency_buffer[128];
int Realpart, Imaginarypart, mod;
int k,n;
int peak,;
int nominal,Frequency;
Int time=clock();


while((clock() - time) / CLOCKS_PER_SEC < 300)       /// processing this program in 5 minutes
{

///////////////////capture the sound data and store it into the buffer/////////////////////////

if ((err = snd_pcm_open (&capture_handle, argv[1], SND_PCM_STREAM_CAPTURE, 0)) < 0) {
    fprintf (stderr, "cannot open audio device %s (%s)\n", 
             argv[1],
             snd_strerror (err));
    exit (1);
  }

  fprintf(stdout, "audio interface opened\n");
		   
  if ((err = snd_pcm_hw_params_malloc (&hw_params)) < 0) {
    fprintf (stderr, "cannot allocate hardware parameter structure (%s)\n",
             snd_strerror (err));
    exit (1);
  }
fprintf(stdout, "hw_params allocated\n");

 if ((err = snd_pcm_hw_params_any (capture_handle, hw_params)) < 0) {
    fprintf (stderr, "cannot initialize hardware parameter structure (%s)\n",
             snd_strerror (err));
    exit (1);
  }

  fprintf(stdout, "hw_params initialized\n");
	
  if ((err = snd_pcm_hw_params_set_access (capture_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
    fprintf (stderr, "cannot set access type (%s)\n",
             snd_strerror (err));
    exit (1);
  }

  fprintf(stdout, "hw_params access setted\n");
	
  if ((err = snd_pcm_hw_params_set_format (capture_handle, hw_params, format)) < 0) {
    fprintf (stderr, "cannot set sample format (%s)\n",
             snd_strerror (err));
    exit (1);
  }

  fprintf(stdout, "hw_params format setted\n");
	
  if ((err = snd_pcm_hw_params_set_rate_near (capture_handle, hw_params, &rate, 0)) < 0) {
    fprintf (stderr, "cannot set sample rate (%s)\n",
             snd_strerror (err));
    exit (1);
  }
	
  fprintf(stdout, "hw_params rate setted\n");

  if ((err = snd_pcm_hw_params_set_channels (capture_handle, hw_params, 2)) < 0) {
    fprintf (stderr, "cannot set channel count (%s)\n",
             snd_strerror (err));
    exit (1);
  }

  fprintf(stdout, "hw_params channels setted\n");
	
  if ((err = snd_pcm_hw_params (capture_handle, hw_params)) < 0) {
    fprintf (stderr, "cannot set parameters (%s)\n",
             snd_strerror (err));
    exit (1);
  }

  fprintf(stdout, "hw_params setted\n");
	
  snd_pcm_hw_params_free (hw_params);

  fprintf(stdout, "hw_params freed\n");
	
  if ((err = snd_pcm_prepare (capture_handle)) < 0) {
    fprintf (stderr, "cannot prepare audio interface for use (%s)\n",
             snd_strerror (err));
    exit (1);
  }

  fprintf(stdout, "audio interface prepared\n");

  buffer = malloc(128 * snd_pcm_format_width(format) / 8 * 2);

  fprintf(stdout, "buffer allocated\n");

  for (i = 0; i < 10; ++i) {
    if ((err = snd_pcm_readi (capture_handle, buffer, buffer_frames)) != buffer_frames) {
      fprintf (stderr, "read from audio interface failed (%s)\n",
               err, snd_strerror (err));
      exit (1);
    }
    fprintf(stdout, "read %d done\n", i);
  }

///////////////////////////////////       DFT            /////////////////////////////////
     Realpart=Imaginary=mod=k=n=0;
     for(k=0;k<=128;k++)
       { for(n=0;n<=128;n++)
        {  Realpart = Realpart + buffer[n]*cos(2*3.14/128*k*n);
          Imaginary = Imaginary - buffer[n]*sin(2*3.14/128*k*n);
          }
       mod = sqrt(Realpart*Realpart + Imaginary*Imaginary);
       Frequency_buffer[k]=mod;
       Realpart=0;
       Imaginarypart=0;
       mod=0;
      }
//////////////////////////////////   pick the peak spectrum  ///////////////////////////////
     
     peak=Frequency_buffer[0];
     nominal=0;
     for(k=0;k<=128;k++)
      { if(peak<Frequency_buffer[k+1])
         {  peak = Frequency_buffer[k+1];
            nominal = k+1;}
      }
    Frequency=nominal*44100/128;
     
//////////////////////////          get the scale         ////////////////////////////////////
      remove("Frequency1");
      remove("Frequency2");
      remove("Scale1");
      remove("Scale2");
      remove("Scale3");

      out = fopen("Frequency1","w");
      fprintf(out,"%d",Frequency);
      fclose(out);

      if(Frequency<15)
      {out = fopen("Frequency2","w");
      fprintf(out,"16.352");
      fclose(out);
      out = fopen("Scale1","w");
      fprintf(out,"C0");
      fclose(out);
      out = fopen("Scale2","w");
      fprintf(out,"Lower");
      fclose(out);
      out = fopen("Scale3","w");
      fprintf(out,"");
      fclose(out);}

      if(15<Frequency&&Frequency<=17)
      {out = fopen("Frequency2","w");
      fprintf(out,"16.352");
      fclose(out);
      out = fopen("Scale1","w");
      fprintf(out,"C0");
      fclose(out);
      out = fopen("Scale2","w");
      fprintf(out,"");
      fclose(out);
      out = fopen("Scale3","w");
      fprintf(out,"");
      fclose(out);}

      if(17<Frequency&&Frequency<=24)
      {out = fopen("Frequency2","w");
      fprintf(out,"16.352");
      fclose(out);
      out = fopen("Scale1","w");
      fprintf(out,"C0");
      fclose(out);
      out = fopen("Scale2","w");
      fprintf(out,"");
      fclose(out);
      out = fopen("Scale3","w");
      fprintf(out,"Higher");
      fclose(out);}

      if(24<=Frequency&&Frequency<=31)
      {out = fopen("Frequency2","w");
      fprintf(out,"32.703");
      fclose(out);
      out = fopen("Scale1","w");
      fprintf(out,"C1");
      fclose(out);
      out = fopen("Scale2","w");
      fprintf(out,"Lower");
      fclose(out);
      out = fopen("Scale3","w");
      fprintf(out,"");
      fclose(out);}

      if(31<Frequency&&Frequency<=34)
      {out = fopen("Frequency2","w");
      fprintf(out,"32.703");
      fclose(out);
      out = fopen("Scale1","w");
      fprintf(out,"C1");
      fclose(out);
      out = fopen("Scale2","w");
      fprintf(out,"");
      fclose(out);
      out = fopen("Scale3","w");
      fprintf(out,"");
      fclose(out);}

      if(34<Frequency&&Frequency<=48)
      {out = fopen("Frequency2","w");
      fprintf(out,"32.703");
      fclose(out);
      out = fopen("Scale1","w");
      fprintf(out,"C1");
      fclose(out);
      out = fopen("Scale2","w");
      fprintf(out,"");
      fclose(out);
      out = fopen("Scale3","w");
      fprintf(out,"Higher");
      fclose(out);}

      if(48<Frequency&&Frequency<=62)
      {out = fopen("Frequency2","w");
      fprintf(out,"65.406");
      fclose(out);
      out = fopen("Scale1","w");
      fprintf(out,"C2");
      fclose(out);
      out = fopen("Scale2","w");
      fprintf(out,"Lower");
      fclose(out);
      out = fopen("Scale3","w");
      fprintf(out,"");
      fclose(out);}

      if(62<Frequency&&Frequency<=68)
      {out = fopen("Frequency2","w");
      fprintf(out,"65.406");
      fclose(out);
      out = fopen("Scale1","w");
      fprintf(out,"C2");
      fclose(out);
      out = fopen("Scale2","w");
      fprintf(out,"");
      fclose(out);
      out = fopen("Scale3","w");
      fprintf(out,"");
      fclose(out);}

      if(68<Frequency&&Frequency<=92)
      {out = fopen("Frequency2","w");
      fprintf(out,"65.406");
      fclose(out);
      out = fopen("Scale1","w");
      fprintf(out,"C2");
      fclose(out);
      out = fopen("Scale2","w");
      fprintf(out,"");
      fclose(out);
      out = fopen("Scale3","w");
      fprintf(out,"Higher");
      fclose(out);}

      if(92<Frequency&&Frequency<=124)
      {out = fopen("Frequency2","w");
      fprintf(out,"130.81");
      fclose(out);
      out = fopen("Scale1","w");
      fprintf(out,"C3");
      fclose(out);
      out = fopen("Scale2","w");
      fprintf(out,"Lower");
      fclose(out);
      out = fopen("Scale3","w");
      fprintf(out,"");
      fclose(out);}

      if(124<Frequency&&Frequency<=137)
      {out = fopen("Frequency2","w");
      fprintf(out,"130.81");
      fclose(out);
      out = fopen("Scale1","w");
      fprintf(out,"C3");
      fclose(out);
      out = fopen("Scale2","w");
      fprintf(out,"");
      fclose(out);
      out = fopen("Scale3","w");
      fprintf(out,"");
      fclose(out);}

      if(137<Frequency&&Frequency<=180)
      {out = fopen("Frequency2","w");
      fprintf(out,"130.81");
      fclose(out);
      out = fopen("Scale1","w");
      fprintf(out,"C3");
      fclose(out);
      out = fopen("Scale2","w");
      fprintf(out,"");
      fclose(out);
      out = fopen("Scale3","w");
      fprintf(out,"Higher");
      fclose(out);}

      if(180<Frequency&&Frequency<=248)
      {out = fopen("Frequency2","w");
      fprintf(out,"261.63");
      fclose(out);
      out = fopen("Scale1","w");
      fprintf(out,"C4");
      fclose(out);
      out = fopen("Scale2","w");
      fprintf(out,"Lower");
      fclose(out);
      out = fopen("Scale3","w");
      fprintf(out,"");
      fclose(out);}

    if(248<Frequency&&Frequency<=274)
      {out = fopen("Frequency2","w");
      fprintf(out,"261.63");
      fclose(out);
      out = fopen("Scale1","w");
      fprintf(out,"C4");
      fclose(out);
      out = fopen("Scale2","w");
      fprintf(out,"");
      fclose(out);
      out = fopen("Scale3","w");
      fprintf(out,"");
      fclose(out);}

    if(274<Frequency&&Frequency<=392)
      {out = fopen("Frequency2","w");
      fprintf(out,"261.63");
      fclose(out);
      out = fopen("Scale1","w");
      fprintf(out,"C4");
      fclose(out);
      out = fopen("Scale2","w");
      fprintf(out,"");
      fclose(out);
      out = fopen("Scale3","w");
      fprintf(out,"Higher");
      fclose(out);}

    if(392<Frequency&&Frequency<=497)
      {out = fopen("Frequency2","w");
      fprintf(out,"523.25");
      fclose(out);
      out = fopen("Scale1","w");
      fprintf(out,"C5");
      fclose(out);
      out = fopen("Scale2","w");
      fprintf(out,"Lower");
      fclose(out);
      out = fopen("Scale3","w");
      fprintf(out,"");
      fclose(out);}

    if(497<Frequency&&Frequency<=549)
      {out = fopen("Frequency2","w");
      fprintf(out,"523.25");
      fclose(out);
      out = fopen("Scale1","w");
      fprintf(out,"C5");
      fclose(out);
      out = fopen("Scale2","w");
      fprintf(out,"");
      fclose(out);
      out = fopen("Scale3","w");
      fprintf(out,"");
      fclose(out);}

    if(549<Frequency&&Frequency<=784)
      {out = fopen("Frequency2","w");
      fprintf(out,"523.25");
      fclose(out);
      out = fopen("Scale1","w");
      fprintf(out,"C5");
      fclose(out);
      out = fopen("Scale2","w");
      fprintf(out,"");
      fclose(out);
      out = fopen("Scale3","w");
      fprintf(out,"Higher");
      fclose(out);}

    if(784<Frequency&&Frequency<=994)
      {out = fopen("Frequency2","w");
      fprintf(out,"1046.5");
      fclose(out);
      out = fopen("Scale1","w");
      fprintf(out,"C6");
      fclose(out);
      out = fopen("Scale2","w");
      fprintf(out,"Lower");
      fclose(out);
      out = fopen("Scale3","w");
      fprintf(out,"");
      fclose(out);}

    if(994<Frequency&&Frequency<=1098)
      {out = fopen("Frequency2","w");
      fprintf(out,"1046.5");
      fclose(out);
      out = fopen("Scale1","w");
      fprintf(out,"C6");
      fclose(out);
      out = fopen("Scale2","w");
      fprintf(out,"");
      fclose(out);
      out = fopen("Scale3","w");
      fprintf(out,"");
      fclose(out);}

    if(1098<Frequency&&Frequency<=1569)
      {out = fopen("Frequency2","w");
      fprintf(out,"1046.5");
      fclose(out);
      out = fopen("Scale1","w");
      fprintf(out,"C6");
      fclose(out);
      out = fopen("Scale2","w");
      fprintf(out,"");
      fclose(out);
      out = fopen("Scale3","w");
      fprintf(out,"Higher");
      fclose(out);}

    if(1569<Frequency&&Frequency<=1988)
      {out = fopen("Frequency2","w");
      fprintf(out,"2093");
      fclose(out);
      out = fopen("Scale1","w");
      fprintf(out,"C7");
      fclose(out);
      out = fopen("Scale2","w");
      fprintf(out,"Lower");
      fclose(out);
      out = fopen("Scale3","w");
      fprintf(out,"");
      fclose(out);}

    if(1988<Frequency&&Frequency<=2197)
      {out = fopen("Frequency2","w");
      fprintf(out,"2093");
      fclose(out);
      out = fopen("Scale1","w");
      fprintf(out,"C7");
      fclose(out);
      out = fopen("Scale2","w");
      fprintf(out,"");
      fclose(out);
      out = fopen("Scale3","w");
      fprintf(out,"");
      fclose(out);}

    if(2197<Frequency&&Frequency<=3139)
      {out = fopen("Frequency2","w");
      fprintf(out,"2093");
      fclose(out);
      out = fopen("Scale1","w");
      fprintf(out,"C7");
      fclose(out);
      out = fopen("Scale2","w");
      fprintf(out,"");
      fclose(out);
      out = fopen("Scale3","w");
      fprintf(out,"Higher");
      fclose(out);}

    if(3139<Frequency&&Frequency<=3976)
      {out = fopen("Frequency2","w");
      fprintf(out,"4186");
      fclose(out);
      out = fopen("Scale1","w");
      fprintf(out,"C8");
      fclose(out);
      out = fopen("Scale2","w");
      fprintf(out,"Lower");
      fclose(out);
      out = fopen("Scale3","w");
      fprintf(out,"");
      fclose(out);}

    if(3976<Frequency&&Frequency<=4395)
      {out = fopen("Frequency2","w");
      fprintf(out,"4186");
      fclose(out);
      out = fopen("Scale1","w");
      fprintf(out,"C8");
      fclose(out);
      out = fopen("Scale2","w");
      fprintf(out,"");
      fclose(out);
      out = fopen("Scale3","w");
      fprintf(out,"");
      fclose(out);}

    if(4395<Frequency&&Frequency<=6279)
      {out = fopen("Frequency2","w");
      fprintf(out,"4186");
      fclose(out);
      out = fopen("Scale1","w");
      fprintf(out,"C8");
      fclose(out);
      out = fopen("Scale2","w");
      fprintf(out,"");
      fclose(out);
      out = fopen("Scale3","w");
      fprintf(out,"Higher");
      fclose(out);}

    if(6279<Frequency&&Frequency<=7953)
      {out = fopen("Frequency2","w");
      fprintf(out,"8372");
      fclose(out);
      out = fopen("Scale1","w");
      fprintf(out,"C9");
      fclose(out);
      out = fopen("Scale2","w");
      fprintf(out,"Lower");
      fclose(out);
      out = fopen("Scale3","w");
      fprintf(out,"");
      fclose(out);}

    if(7953<Frequency&&Frequency<=8790)
      {out = fopen("Frequency2","w");
      fprintf(out,"8372");
      fclose(out);
      out = fopen("Scale1","w");
      fprintf(out,"C9");
      fclose(out);
      out = fopen("Scale2","w");
      fprintf(out,"");
      fclose(out);
      out = fopen("Scale3","w");
      fprintf(out,"");
      fclose(out);}

    if(Frequency>8790)
      {out = fopen("Frequency2","w");
      fprintf(out,"8372");
      fclose(out);
      out = fopen("Scale1","w");
      fprintf(out,"C9");
      fclose(out);
      out = fopen("Scale2","w");
      fprintf(out,"");
      fclose(out);
      out = fopen("Scale3","w");
      fprintf(out,"Higher");
      fclose(out);}

    printf("k = %d\n",k);
    printf("Frequency = %d\n",Frequency);
    printf("use_buf3[0]=%d\n",use_buf3[0]);
    printf("buf=%d\n,%d\n,%d\n",buf[0],buf[128],buf[256]);
       
      free(buffer);
      sleep(2); }
     
  }  

///////////////////////// close the program //////////////////////////////////////////////
 
snd_pcm_close (capture_handle);
fprintf(stdout, "audio interface closed\n");
return 0;

}