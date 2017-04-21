if love.system.getOS() == "Linux" then
  return require "espeak"
elseif love.system.getOS() == "OS X" then
  -- idk
  -- return require "espeak"
else
  return require "SAPI"
end
