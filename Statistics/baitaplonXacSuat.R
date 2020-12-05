#A.Hoi quy tuyen tinh
#Bai tap 1:
#1.
giaNha <- read.csv("C:\\Users\\Thanh Vo\\Desktop\\BaiTapLon\\gia_nha.csv", header = TRUE)
#2a.
new_DF <- giaNha[, c(6, 9, 11, 14, 16, 23)]
#2b
new_DF <- na.omit(new_DF)
#3a
new_DF$price <- log(new_DF$price)
new_DF$sqft_living15 <- log(new_DF$sqft_living15)
new_DF$sqft_above <- log(new_DF$sqft_above)
new_DF$sqft_living <- log(new_DF$sqft_living)
#3b
price <- c(mean(new_DF$price), median(new_DF$price), sd(new_DF$price), min(new_DF$price), max(new_DF$price))
sqft_living15 <- c(mean(new_DF$sqft_living15), median(new_DF$sqft_living15), sd(new_DF$sqft_living15), min(new_DF$sqft_living15), max(new_DF$sqft_living15))
sqft_above <- c(mean(new_DF$sqft_above), median(new_DF$sqft_above), sd(new_DF$sqft_above), min(new_DF$sqft_above), max(new_DF$sqft_above))
sqft_living <- c(mean(new_DF$sqft_living), median(new_DF$sqft_living), sd(new_DF$sqft_living), min(new_DF$sqft_living), max(new_DF$sqft_living))
table <- data.frame(price, sqft_living15, sqft_above, sqft_living)
row.names(table) <- c("mean", "median", "sd", "min", "max")
#3c
#new_DF$floors <- factor(new_DF$floors)
table(new_DF$floors)
#new_DF$condition <- factor(new_DF$condition)
table(new_DF$condition)
#3d
hist(new_DF$price)
#3e
boxplot(price~floors, data = new_DF, main="Boxplot for each floors")
boxplot(price~condition, data = new_DF, main="Boxplot for each condition")
#3f
#pairs(price~sqft_above+sqft_living+sqft_living15, data = new_DF)
#4a
mulfit <- lm(price~sqft_above+sqft_living+sqft_living15+floors+condition , data = new_DF)
mulfit
