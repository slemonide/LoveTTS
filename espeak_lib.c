#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <espeak/speak_lib.h>

void *
mllc(int sz)
{
    void *ret = malloc(sz);
    if (!ret) {
        fprintf(stderr, "fatal memory error\n");
        exit(3);
    }
    return ret;
}

void *
rllc(void *ptr, int sz)
{
    void *temp = realloc(ptr, sz);
    if (!temp) {
        fprintf(stderr, "fatal memory error\n");
        exit(3);
    }
    return temp;
}

//

#define BASE_SOUND_ARRAY_SIZE 2048

typedef struct {
    short *samples;
    uint64_t sample_max;
    uint64_t sample_ct;
} sound_array;

void
sound_array_init(sound_array *sa)
{
    sa->samples = mllc(sizeof(short) * BASE_SOUND_ARRAY_SIZE);
    sa->sample_max = BASE_SOUND_ARRAY_SIZE;
    sa->sample_ct = 0;
}

void
sound_array_deinit(sound_array *sa)
{
    if (sa->samples)
        free(sa->samples);
    sa->samples = NULL;
    sa->sample_ct = 0;
    sa->sample_max = 0;
}

void
sound_array_clear(sound_array *sa)
{
    sound_array_deinit(sa);
    sound_array_init(sa);
}

void
sound_array_push(sound_array *sa, const short *samples, int ct)
{
    if (!ct) return;

    if (sa->sample_max < sa->sample_ct + ct) {
        uint64_t resize_ct = sa->sample_max * 1.5 + ct * 2;
        sa->samples = rllc(sa->samples, sizeof(short) * resize_ct);
        sa->sample_max = resize_ct;
    }

    memcpy(&sa->samples[sa->sample_ct]
         , samples
         , ct * sizeof(short));
    sa->sample_ct += ct;
}

void
sound_array_finish(sound_array *sa)
{
    sa->samples = rllc(sa->samples, sizeof(short) * sa->sample_ct);
    sa->sample_max = sa->sample_ct;
}

//

sound_array main_array;

int
espeak_callback(short *buf, int sz, espeak_EVENT *ev)
{
    (void) ev;
    if (buf) {
        sound_array_push(&main_array, buf, sz);
    } else {
        sound_array_finish(&main_array);
    }
    return 0;
}

//

int rate;

ESPEAK_API int
espeak_init()
{
    sound_array_init(&main_array);

    rate = espeak_Initialize(AUDIO_OUTPUT_SYNCHRONOUS, 0, NULL, 0);
    if (rate == -1)
        return 1;
    espeak_SetSynthCallback(espeak_callback);

    return 0;
}

ESPEAK_API void
espeak_deinit()
{
    sound_array_deinit(&main_array);
    espeak_Terminate();
}

ESPEAK_API void
copy(void *into, int ct)
{
    memcpy(into, main_array.samples, ct * sizeof(short));
}

ESPEAK_API int
get_count()
{
    return main_array.sample_ct;
}

ESPEAK_API int
speak(const char *words)
{
    sound_array_clear(&main_array);

    int err = espeak_Synth(words, 0, 0, POS_CHARACTER, 0, espeakCHARS_AUTO, NULL, NULL);
    if (err) {
        fprintf(stderr, "espeak synth error: %d\n", err);
        return err;
    }

    return 0;
}
