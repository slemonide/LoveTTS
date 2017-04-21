### LoveTTS  

Text to Speech for Love2D!  
work in progress (works on Linux)  

#### to build:  
Linux!  
&nbsp;&nbsp;install eSpeak from your package manager  
&nbsp;&nbsp;$ ./build  

Windows.  
&nbsp;&nbsp;install Microsoft SAPI [download link](https://download.microsoft.com/download/B/4/3/B4314928-7B71-4336-9DE7-6FA4CF00B7B3/SpeechSDK51.exe)  
&nbsp;&nbsp;install [LuaCOM](https://github.com/davidm/luacom)  
&nbsp;&nbsp;download [this](https://github.com/fiendish/MS_Speech_API_Lua) and put it where Lua can find it  

#### to use:  
&nbsp;&nbsp;main.lua is an example!  

#### API  
```lua
local tts = require "tts"

-- table? -> void
tts.init(params = nil)
-- initialize tts
-- params table explained below
-- warning: can raise an error (unlikely)
-- warning: remember to call tts.deinit during love.quit

-- void -> void
tts.deinit()
-- deinit tts

-- table? -> void [linux only]
tts.set_params(params = nil)
-- set voice parameters
-- takes a table where keys match the parameters below
-- options are:
--   > rate        - words per minute     (number 80 - 450)
--   > volume      - volume               (number 0 - 200 = 100) (0 is silent, 100 is 'normal')
--   > pitch       - base pitch           (number 0 - 100 = 50) (50 is 'normal')
--   > range       - pitch range          (number 0 - 100 = 50) (0 is monotone, 50 is 'normal')
--   > punctuation - announce punctuation [not yet implemented]
--   > capitals    - announce capitals    [not yet implemented]
--   > word_gap    - pause between words  (number units of 10 millisec (at default speed))

-- string, boolean? -> int [linux only]
tts.get_param(name, get_default = false)
-- get voice parameter
-- if get_default == true then
--   return tts's default
-- else
--   return current value
-- end

-- string -> love.audio.Source
tts.say(words)
-- say the words
-- will return a love.audio.Source that can be played as an audio file
-- warning: this function blocks, best to be called during the love.load function
-- warning: can raise an error (unlikely)
-- warning: does not return a love.audio.Source on Windows, yet (or maybe, ever)
--          instead returns just some object that you can call :play() on

-- [not yet implemented]
tts.print_voices()

-- [not yet implemented]
tts.set_voice()
```

#### todo:  
+ cross-platform  
+ support different voices  
+ make sure dynamic libs are installable/findable when Love2D runs  

#### license:  
&nbsp;&nbsp;GPL.... i guess \\(-_-
