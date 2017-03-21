local espeak = require "espeak"

function love.load()
  espeak.init({
    rate = 80 ,
    range = 0 ,
    pitch = 10 ,
  })
  local words = espeak.say("weoooooo weoooo wawawaaaa")

  espeak.set_params({
    rate = 10 ,
    range = 50 ,
    pitch = 50
  })
  local words2 = espeak.say("love love love love love love love")

  words:play()
  words2:play()
end

function love.quit()
  espeak.deinit()
end
