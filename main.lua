local tts = require "tts"

 function love.load()
  tts.init()
  local words = tts.say("weoooooo weoooo wawawaaaa")
  words:play()
end

function love.quit()
  tts.deinit()
end
