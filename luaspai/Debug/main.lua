local string = require "string"
local fmt = string.format

local ffi = require "ffi"

ffi.cdef [[
bool init_sapi();
void deinit_sapi();
bool speak(const char *);
unsigned long get_size();
unsigned long fill_buffer(unsigned char *buf, unsigned long sz);
]]

local sapi = ffi.load("luaspai.dll")

local tts = {}

tts.initialized = false

function tts.get_voices()
	-- unimplemented
	-- return {string}
end

function tts.set_voice(to)
end

function tts.init()
	sapi.init_sapi()
	tts.initialized = true
end

function tts.deinit()
	sapi.deinit_sapi()
	tts.initalized = false
end

function tts.say(words, debug_info)
	if not tts.initialized then
		error(fmt("cannot say '%s', tts has not been initialized", words))
		return
	end

    sapi.speak(words)
	local sz = sapi.get_size()

	local data = love.sound.newSoundData(sz, 44100, 16, 2)
	sapi.fill_buffer(data:getPointer(), sz)

	if debug_info then
		print(fmt("said '%s' bytes: %d", words, sz))
	end

	return love.audio.newSource(data)
end

function love.load()
	tts.init()
	local data = tts.say("hello from lua", true)
	data:play()
	local data2 = tts.say("wowow", true)
	data2:play()
end

function love.draw()
end

function love.quit()
	tts.deinit()
end