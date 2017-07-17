local tts = require "tts"

 function love.load()
  tts.init()
  local words = tts.say("hello world")
  words:play()
end

function love.quit()
  tts.deinit()
end
