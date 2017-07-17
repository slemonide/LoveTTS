local espeak = {}

local ffi = require "ffi"
ffi.cdef [[
int espeak_init();
void espeak_deinit();
void copy(void *, int ct);
int get_count();
int speak(const char *);

int rate;
]]
local espk = ffi.load "./espeak_lib.so"

--

local initialized = false

function espeak.init()
  if espk.espeak_init() ~= 0 then
    error("espeak init error")
  end
  initialized = true
end

function espeak.deinit()
  espk.espeak_deinit()
  initalized = false
end

function espeak.say(words)
  if not initialized then
      error("please init espeak before use")
  end

  if espk.speak(words) ~= 0 then
    error("espeak words error")
  end

  local data = love.sound.newSoundData(espk.get_count(), espk.rate, 16, 1)
  espk.copy(data:getPointer(), espk.get_count())
  return love.audio.newSource(data)
end

return espeak
