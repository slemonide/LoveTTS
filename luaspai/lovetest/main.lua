local ffi = require "ffi"

ffi.cdef [[
int call_me(); int init_sapi();
]]

local x = ffi.load("luaspai.dll")

 x.init_sapi() function love.draw()
love.graphics.print(x.call_me())
end
