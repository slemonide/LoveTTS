local espeak = {}

local ffi = require "ffi"
ffi.cdef [[
void copy_main_array(void *);
int do_speak(const char *);
int espeak_init(int *);
void espeak_deinit();

int espeak_SetParameter(int, int, int);
]]
local lib_espeak = ffi.load "./espeak_lib.so"

local sample_rate = "invalid sample rate"
function espeak.init(t)
  local rate = ffi.new("int[1]")
  lib_espeak.espeak_init(rate)
  sample_rate = rate[0]
  espeak.set_params(t)
end

function espeak.deinit()
  lib_espeak.espeak_deinit()
end

function espeak.set_params(t)
  if t and type(t) == "table" then
    resolve = {
      rate = 1 ,
      volume = 2 ,
      pitch = 3 ,
      range = 4 ,
      punctuation = 5 ,
      capitals = 6 ,
      wordgap = 7 ,
      intonation = 9
    }
    for k, v in pairs(t) do
      if resolve[k] then
        lib_espeak.espeak_SetParameter(resolve[k], v, 0)
      else
        print("invalid espeak param:", k)
      end
    end
  end
end

function espeak.say(words)
  local sz = lib_espeak.do_speak(words)
  if sz < 0 then
    return nil
  end

  local data = love.sound.newSoundData(sz, sample_rate, 16, 1)
  lib_espeak.copy_main_array(data:getPointer())
  return love.audio.newSource(data)
end

return espeak
