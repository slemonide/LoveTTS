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

int
main (void)
{
    sound_array_test();
    return 0;

    int sample_rate;
    espeak_init(&sample_rate);
    printf("%d\n", sample_rate);

    int err = do_speak("hello there hows it going wadadada long long long words.");
    if (err) return 1;

    printf("final %d %d\n", main_array.sample_ct, main_array.sample_max);
    espeak_deinit();

    return 0;
}
