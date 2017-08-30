x = Random.new
y = Random.new
num = Random.new

#x = rand(1..140)
#y = rand(1..140)

x = 103
y = 103

puts x
puts y

for i in 0..x-1 do
  for j in 0..y-1 do
    num = rand(1..20)
    print format('%2d ', num)
  end
  puts "\n"
end
