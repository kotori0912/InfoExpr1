#多倍長整数自動生成プログラム

rnum = Random.new
num = Random.new
rnum = rand(1..50)

puts rnum+1

for i in 0..rnum do
  num = rand(0..99999999)
  print format('%08d ', num)
end

puts "\n"
