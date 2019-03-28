setTickRate(30)
function onTick()
  id, ext, data = rxCAN(0)
  if (id ~= nil) then
    txCAN(1, id, ext, data)
  end

end

