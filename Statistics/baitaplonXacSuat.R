
#Bai tap 1:
#1.
giaNha <- read.csv("C:\\Users\\Thanh Vo\\OneDrive\\Desktop\\BaiTapLon\\gia_nha.csv", header = TRUE)
#2a.
new_DF <- giaNha[, c(6, 9, 11, 14, 16, 23)]
#2b
new_DF <- na.omit(new_DF)#xóa hàng ch???a NA
#3a
new_DF$price <- log(new_DF$price)
new_DF$sqft_living15 <- log(new_DF$sqft_living15)
new_DF$sqft_above <- log(new_DF$sqft_above)
new_DF$sqft_living <- log(new_DF$sqft_living)
#3b
price <- c(mean(new_DF$price), median(new_DF$price), 
           sd(new_DF$price), min(new_DF$price), max(new_DF$price))
sqft_living15 <- c(mean(new_DF$sqft_living15), median(new_DF$sqft_living15), 
                   sd(new_DF$sqft_living15), min(new_DF$sqft_living15), 
                   max(new_DF$sqft_living15))
sqft_above <- c(mean(new_DF$sqft_above), median(new_DF$sqft_above), 
                sd(new_DF$sqft_above), min(new_DF$sqft_above), max(new_DF$sqft_above))
sqft_living <- c(mean(new_DF$sqft_living), median(new_DF$sqft_living), 
                 sd(new_DF$sqft_living), min(new_DF$sqft_living), 
                 max(new_DF$sqft_living))
table <- data.frame(price, sqft_living15, sqft_above, sqft_living)
row.names(table) <- c("mean", "median", "sd", "min", "max")
table
#3c
table( new_DF$floors)
table(new_DF$condition)
#3d
hist(new_DF$price)
#3e
plot(new_DF$price, new_DF$sqft_above)
boxplot(price~floors, data = new_DF
        , main="Boxplot for each floors")
boxplot(price~condition, data = new_DF, 
        main="Boxplot for each condition")
#3f
pairs(price~sqft_above+sqft_living+
        sqft_living15, data = new_DF)
#4a
m1 <- lm(price~sqft_above+sqft_living+
           sqft_living15+floors+condition , 
            data = new_DF)
summary(m1)
m2 <- lm(price~sqft_above+sqft_living+
           sqft_living15+floors , data = new_DF)
anova(m2, m1)
plot(m1, which =1)
#4c

x1_data = data.frame(sqft_living15 = mean(new_DF$sqft_living15),
                     sqft_above = mean(new_DF$sqft_above),
                     sqft_living= mean(new_DF$sqft_living),
                     floors = 2,
                     condition = 3
)
predict(m1,x1_data,interval = "confidence")
x2_data = data.frame(sqft_living15 = max(new_DF$sqft_living15),
                     sqft_above =max(new_DF$sqft_above),
                     sqft_living = max(new_DF$sqft_living),
                     floors = 2,
                     condition = 3
)
predict(m1,x2_data,interval = "confidence")

