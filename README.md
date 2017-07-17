### LoveTTS  

Text to Speech for Love2D!  
work in progress  

#### to build:  
Linux!  
&nbsp;&nbsp;install eSpeak from your package manager  
&nbsp;&nbsp;$ ./build  

Windows.  
&nbsp;&nbsp;install Microsoft SAPI [download link](https://download.microsoft.com/download/B/4/3/B4314928-7B71-4336-9DE7-6FA4CF00B7B3/SpeechSDK51.exe)  

#### to use:  
&nbsp;&nbsp;main.lua is an example!  

#### API  
```lua
local tts = require "tts"

tts.init()
-- initialize tts
-- warning: can raise an error (unlikely)

tts.deinit()
-- deinit tts

-- string -> love.audio.Source
tts.say(words)
-- takes a string
-- returns a love.audio.Sourcs
-- warning: this function blocks, best to be called during the love.load function
-- warning: can raise an error (unlikely)

-- [not yet implemented]
tts.get_voices()
-- returns a table of strings

-- [not yet implemented]
tts.set_voice(to)
-- takes a string
-- sets the voice
```

#### todo:  
+ cross-platform  
+ support different voices  
+ make sure dynamic libs are installable/findable when Love2D runs  

#### license:  
&nbsp;&nbsp;GPL.... i guess \\(-_-
