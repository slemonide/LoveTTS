local interface

local SAPI = {}

function SAPI.init(t)
  interface = require "sapi_interface"
  if interface == -1 then
    error("could not open SAPI")
  elseif interface = -2 then
    error("no SAPI voices found")
  end
end

function SAPI.deinit()
end

function SAPI.set_params(t)
end

function SAPI.get_param(name, get_default)
end

function SAPI.say(words)
  return {
    words = words ,

    play = function (self)
      interface.say(self.words)
    end

    clone = function (self)
      return SAPI.say(words)
    end ,

    getAttenuationDistances = function (self) end ,
    getChannels = function (self) end ,
    getCone = function (self) end ,
    getDirection = function (self) end ,
    getDistance = function (self) end ,
    getDuration = function (self) end ,
    getPitch = function (self) end ,
    getPosition = function (self) end ,
    getRolloff = function (self) end ,
    getType = function (self) end ,
    getVelocity = function (self) end ,
    getVolume = function (self) end ,
    getVolumeLimits = function (self) end ,
    isLooping = function (self) end ,
    isPaused = function (self) end ,
    isPlaying = function (self) end ,
    isRelative = function (self) end ,
    isStatic = function (self) end ,
    isStopped = function (self) end ,
    pause = function (self) end ,
    resume = function (self) end ,
    rewind = function (self) end ,
    seek = function (self) end ,
    setAttenuationDistances = function (self) end ,
    setCone = function (self) end ,
    setDirection = function (self) end ,
    setDistance = function (self) end ,
    setLooping = function (self) end ,
    setPitch = function (self) end ,
    setPosition = function (self) end ,
    setRelative = function (self) end ,
    setRolloff = function (self) end ,
    setVelocity = function (self) end ,
    setVolume = function (self) end ,
    setVolumeLimits = function (self) end ,
    stop = function (self) end ,
    tell = function (self) end ,

  }
end

return SAPI
