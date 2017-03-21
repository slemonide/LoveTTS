### LoveTTS  

Text to Speech for Love2D!  
work in progress (works on Linux)  

#### to build:  
&nbsp;&nbsp;install eSpeak from your package manager  
&nbsp;&nbsp;$ ./build  

#### to use:  
&nbsp;&nbsp;main.lua is an example!  
```lua
local espeak = require "espeak"
```

#### API  
```lua
-- table? -> void
espeak.init(params = nil)
-- initialize espeak
-- params table explained below
-- warning: can raise an error
-- warning: remember to call espeak.deinit during love.quit

-- void -> void
espeak.deinit()
-- deinit espeak

-- table? -> void
espeak.set_params(params = nil)
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

-- string, boolean? -> int
espeak.get_param(name, get_default = true)
-- get voice parameter
-- if get_default == true then
--   return espeak's default
-- else
--   return current value
-- end

-- string -> love.audio.Source
espeak.say(words)
-- say the words
-- will return a love.audio.Source that can be played as an audio file
-- warning: this function blocks, best to be called during the love.load function
-- warning: can raise error

-- [not yet implemented]
espeak.print_voices()

-- [not yet implemented]
espeak.set_voice()
```

#### todo:  
+ cross-platform  
+ support different voices  
+ make sure dynamic libs are installable  

#### license:  
&nbsp;&nbsp;this may have to be GPL because of espeak, gimme a sec lol  
&nbsp;&nbsp;i'll get back to you  
