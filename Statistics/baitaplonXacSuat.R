#A.Hoi quy tuyen tinh
#Bai tap 1:
#1.
giaNha <- read.csv("C:\\Users\\Thanh Vo\\Desktop\\BaiTapLon\\gia_nha.csv", header = TRUE)
#2a.
new_DF <- giaNha[, c(6, 9, 11, 14, 16, 23)]
#2b
new_DF <- na.omit(new_DF)
