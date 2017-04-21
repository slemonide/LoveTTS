local espeak = {}

local ffi = require "ffi"
ffi.cdef [[
int espeak_init(int *);
void espeak_deinit();
void main_array_copy(void *);
int do_speak(const char *, int *);

int espeak_SetParameter(int, int, int);
int espeak_GetParameter(int, int);
]]
local lib_espeak = ffi.load "./espeak_lib.so"

--

local sample_rate

local espeak_params = {
  rate = 1 ,
  volume = 2 ,
  pitch = 3 ,
  range = 4 ,
  -- punctuation = 5 ,
  -- capitals = 6 ,
  word_gap = 7 ,
}

function espeak.init(t)
  local rate = ffi.new("int[1]")
  if lib_espeak.espeak_init(rate) ~= 0 then
    error("espeak init error")
  end
  sample_rate = rate[0]
  espeak.set_params(t)
end

function espeak.deinit()
  lib_espeak.espeak_deinit()
end

function espeak.set_params(t)
  if t and type(t) == "table" then
    for k, v in pairs(t) do
      if espeak_params[k] then
        lib_espeak.espeak_SetParameter(espeak_params[k], v, 0)
      else
        print("invalid espeak param:", k)
      end
    end
  end
end

function espeak.get_param(name, get_default)
  if get_default == true then
    get_default = 0
  else
    get_default = 1
  end

  if espeak_params[name] then
    return lib_espeak.espeak_getParameter(espeak_params[name], get_default)
  else
    print("invalid espeak param:", name)
  end
end

function espeak.say(words)
  if not sample_rate then
      error("please init espeak before use")
  end

  local sz = ffi.new("int[1]")
  if lib_espeak.do_speak(words, sz) ~= 0 then
    error("espeak synth error")
  end

  local data = love.sound.newSoundData(sz[0], sample_rate, 16, 1)
  lib_espeak.main_array_copy(data:getPointer())
  return love.audio.newSource(data)
end

return espeak
