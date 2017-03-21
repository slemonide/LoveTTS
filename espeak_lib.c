#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <espeak/speak_lib.h>

#define BASE_SOUND_ARRAY_SIZE 2048

typedef struct {
    short *samples;
    uint64_t sample_max;
    uint64_t sample_ct;
} sound_array;

int
sound_array_init(sound_array *sa)
{
    sa->samples = malloc(sizeof(short) * BASE_SOUND_ARRAY_SIZE);
    if (!sa->samples)
        return 1;

    sa->sample_max = BASE_SOUND_ARRAY_SIZE;
    sa->sample_ct = 0;
    return 0;
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

int
sound_array_clear(sound_array *sa)
{
    sound_array_deinit(sa);
    return sound_array_init(sa);
}

int
sound_array_push(sound_array *sa, const short *samples, int ct)
{
    if (!ct) return 0;

    if (sa->sample_max < sa->sample_ct + ct) {
        uint64_t resize_ct = sa->sample_max * 1.5 + ct * 2;
        short *temp = realloc(sa->samples, sizeof(short) * resize_ct);
        if (!temp)
            return 1;
        sa->samples = temp;
        sa->sample_max = resize_ct;
    }

    memcpy(&sa->samples[sa->sample_ct]
         , samples
         , ct * sizeof(short));
    sa->sample_ct += ct;
    return 0;
}

int
sound_array_finish(sound_array *sa)
{
    short *temp = realloc(sa->samples, sizeof(short) * sa->sample_ct);
    if (!temp)
        return 1;
    sa->samples = temp;
    sa->sample_max = sa->sample_ct;
    return 0;
}

#if 0

#include <assert.h>

void
sound_array_test()
{
#define BUFFER_SZ 1500
    short buffer[BUFFER_SZ];
    memset(buffer, 0, BUFFER_SZ);

    sound_array x;
    sound_array_init(&x);
    assert(x.sample_ct == 0);
    assert(x.sample_max == BASE_SOUND_ARRAY_SIZE);

    sound_array_push(&x, buffer, BUFFER_SZ);
    assert(x.sample_ct == BUFFER_SZ);
    assert(x.sample_max == BASE_SOUND_ARRAY_SIZE);

    sound_array_push(&x, buffer, BUFFER_SZ);
    assert(x.sample_ct == BUFFER_SZ * 2);
    assert(x.sample_max > BASE_SOUND_ARRAY_SIZE);

    sound_array_finish(&x);
    assert(x.sample_ct == BUFFER_SZ * 2);
    assert(x.sample_max == BUFFER_SZ * 2);

    sound_array_deinit(&x);
}

#endif

// =================================== //

sound_array main_array;

int
espeak_callback(short *buf, int sz, espeak_EVENT *ev)
{
    (void) ev;
    int err = 0;
    if (buf)
        err = sound_array_push(&main_array, buf, sz);
    else
        err = sound_array_finish(&main_array);

    return err;
}

void
copy_main_array(void *into)
{
    memcpy(into, main_array.samples, main_array.sample_ct * sizeof(short));
}

int
do_speak(const char *words)
{
    sound_array_clear(&main_array);
    int err = espeak_Synth(words, 0, 0, POS_CHARACTER, 0, espeakCHARS_AUTO, NULL, NULL);
    if (err) {
        printf("epeak synth error: %d\n", err);
        return -1;
    }

    return main_array.sample_ct;
}

int
espeak_init(int *rate)
{
    sound_array_init(&main_array);
    *rate = espeak_Initialize(AUDIO_OUTPUT_SYNCHRONOUS, 0, NULL, 0);
    espeak_SetSynthCallback(espeak_callback);
    return 0;
}

void
espeak_deinit()
{
    sound_array_deinit(&main_array);
}

#if 0
int
main (void)
{
#if 0
    sound_array_test();
    return 0;
#endif

    int sample_rate;
    espeak_init(&sample_rate);
    printf("%d\n", sample_rate);

    int err = do_speak("hello there hows it going wadadada long long long words.");
    if (err) return 1;

    printf("final %d %d\n", main_array.sample_ct, main_array.sample_max);
    espeak_deinit();

    return 0;
}
#endif
