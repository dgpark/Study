# 1.read dataset
data = read.csv("C:\\Users\\dgpar\\Desktop\\MarketingResearch\\coffee_data2.csv")
head(data)
colnames(data) <- c("id", "consumePerWeek", "buyingTime", "PurposeOfBuying", "rationalPrice", "weightTaste", "weightPrice", "weightBrand","weightAtmosphere", "weightVariety", "requirement", "taste1", "taste2", "taste3", "taste4", "taste5", "saving1", "saving2", "saving3", "saving4", "saving5", "health1", "health2", "health3", "health4", "cultural1", "cultural2", "cultural3", "cultural4" ,"sociality1", "sociality2", "sociality3", "sociality4", "sociality5", "trend1", "trend2", "trend3", "trend4", "trend5", "gender", "age", "educationLevel", "livingStyle", "occupation", "income1", "income2", "eatingOutExpenses")
head(data)


#data preprocessing.
df <- data.frame(data$id)
# column1
data$consumePerWeek <- gsub("0번", 0, data$consumePerWeek)
data$consumePerWeek <- gsub("1~3번", 2, data$consumePerWeek)
data$consumePerWeek <- gsub("4~6번", 5, data$consumePerWeek)
data$consumePerWeek <- gsub("7~9번", 8, data$consumePerWeek)
data$consumePerWeek <- gsub("10~12번", 11, data$consumePerWeek)
data$consumePerWeek <- gsub("13번 이상", 14, data$consumePerWeek)
data$consumePerWeek <- as.numeric(data$consumePerWeek)
head(data$consumePerWeek)
consumePerWeek <- data$consumePerWeek
df <- cbind(df, consumePerWeek)

data$rationalPrice <- gsub("2000원 미만", 1500, data$rationalPrice)
data$rationalPrice <- gsub("2000원 이상~3000원 미만", 2500, data$rationalPrice)
data$rationalPrice <- gsub("3000원 이상~4000원 미만", 3500, data$rationalPrice)
data$rationallePrice <- gsub("4000원 이상", 4500, data$rationalPrice)
data$rationalPrice <- as.numeric(data$rationalPrice)
rationalPrice <- data$rationalPrice
df <- cbind(df, rationalPrice)

colnames(data)
for(i in 6:10){
  data[,i] <- gsub("1점", 1, data[,i])
  data[,i] <- gsub("2점", 2, data[,i])
  data[,i] <- gsub("3점", 3, data[,i])
  data[,i] <- gsub("4점", 4, data[,i])
  data[,i] <- gsub("5점", 5, data[,i])
  data[,i] <- as.numeric(data[,i])
}

weightTaste <- data$weightTaste
df <- cbind(df, weightTaste)
weightPrice <- data$weightPrice
df <- cbind(df, weightPrice)
weightBrand <- data$weightBrand
df <- cbind(df, weightBrand)
weightAtmosphere <- data$weightAtmosphere
df <- cbind(df, weightAtmosphere)
weightVariety <- data$weightVariety
df <- cbind(df, weightVariety)

#summation of taste
colnames(data)
for(i in 12:39){
  data[,i] <- gsub("매우 그렇지 않다", 1, data[,i])
  data[,i] <- gsub("그렇지 않다", 2, data[,i])
  data[,i] <- gsub("보통이다", 3, data[,i])
  data[,i] <- gsub("매우 그렇다", 5, data[,i])
  data[,i] <- gsub("그렇다", 4, data[,i])
  data[,i] <- as.numeric(data[,i])
}
taste <- 0 
taste[1:length(data[,1])] <- 0

colnames(data)
for(i in 12:16){
  for(j in 1:length(data[,1]))
    taste[j] = taste[j] + data[j,i]
}
head(taste)

df <- cbind(df, taste)
df

# summation of saving
saving <- 0
saving[1:length(data[,1])] <- 0

colnames(data)
for(i in 17:21){
  for(j in 1:length(data[,1]))
    saving[j] = saving[j] + data[j,i]
}
head(saving)

df <- cbind(df, saving)
df

# summation of health
health <- 0
health[1:length(data[,1])] <- 0

colnames(data)
for(i in 22:25){
  for(j in 1:length(data[,1]))
    health[j] = health[j] + data[j,i]
}
head(health)

df <- cbind(df, health)
df

# summation of cultural
cultural <- 0
cultural[1:length(data[,1])] <- 0

colnames(data)
for(i in 26:29){
  for(j in 1:length(data[,1]))
    cultural[j] = cultural[j] + data[j,i]
}
head(cultural)

df <- cbind(df, cultural)
df

# summation of sociality
sociality <- 0
sociality[1:length(data[,1])] <- 0

colnames(data)
for(i in 30:34){
  for(j in 1:length(data[,1]))
    sociality[j] = sociality[j] + data[j,i]
}
head(sociality)

df <- cbind(df, sociality)
df

# summation of trend
trend <- 0
trend[1:length(data[,1])] <- 0

colnames(data)
for(i in 35:39){
  for(j in 1:length(data[,1]))
    trend[j] = trend[j] + data[j,i]
}
head(trend)

df <- cbind(df, trend)
df

# income
data$income1 <- gsub("30만원 미만", 20, data$income1)
data$income1 <- gsub("30만원 이상~50만원 미만", 40, data$income1)
data$income1 <- gsub("50만원 이상~70만원 미만", 60, data$income1)
data$income1 <- gsub("70만원 이상~90만원 미만", 80, data$income1)
data$income1 <- gsub("90만원이상~110만원 미만", 100, data$income1)
data$income1 <- gsub("110만원 이상", 130, data$income1)
data$income1 <- as.numeric(data$income1)
#mean(data$income1, na.rm = T)
#data$income1[3] %in% NA
#data$income1[3]


data$income2 <- gsub("100만원 미만", 70, data$income2) # 인턴intern등의 월급 평균? 
data$income2 <- gsub("100만원 이상~200만원 미만", 150, data$income2)
data$income2 <- gsub("200만원 이상~300만원 미만", 250, data$income2)
data$income2 <- gsub("300만원 이상~400만원 미만", 350, data$income2)
data$income2 <- gsub("400만원 이상~500만원 미만", 450, data$income2)
data$income2 <- as.numeric(data$income2)
#data$income2[2] %in% NA

data$income1[1]
income <- data$income1[1]
for(i in 2:length(data[,1])){
  if(data$income1[i] %in% NA){
    income <- append(income, data$income2[i])
  }
  else{
    income <- append(income, data$income1[i])
  }
}
income
data$income1[11]
df <- cbind(df, income)
df

data$age <- gsub("20세~22세", 1, data$age)
data$age <- gsub("23세~26세", 2, data$age)
data$age <- gsub("27세~29세", 3, data$age)
data$age <- as.numeric(data$age)
age <- data$age

df <- cbind(df, age)

data$gender <- gsub("남", 1, data$gender)
data$gender <- gsub("여", 2, data$gender)
data$gender <- as.numeric(data$gender)
gender <- data$gender
df <- cbind(df, gender)

df <- na.omit(df)
df

# 2.Check the distribution
par(mfrow=c(1,1))
hist(df$consumePerWeek) # frequency of buy
hist(df$rationalPrice) # wanted price
hist(df$consumePerWeek * df$rationalPrice)
hist(log(df$consumePerWeek * df$rationalPrice))

par(mfrow=c(2,2))
hist(df$weightTaste)
hist(df$weightPrice)
hist(df$weightBrand)
hist(df$weightAtmosphere)
hist(df$weightVariety)

hist(df$taste)
hist(df$saving)
hist(df$health)
hist(df$cultural)
hist(df$sociality)
hist(df$trend)

###########################Multiple Regression test
priceMcount = df$consumePerWeek[1] * df$rationalPrice[1]

for(i in 2:length(df[,1])){
  priceMcount <- append(priceMcount, df$consumePerWeek[i]*df$rationalPrice[i])
}
priceMcount

summary(lm(priceMcount ~ df$taste + df$saving + df$cultural + df$sociality + df$trend))

summary(lm(priceMcount ~ df$saving + df$cultural + df$sociality + df$trend))

summary(lm(priceMcount ~ df$saving + df$sociality + df$trend))

summary(lm(priceMcount ~ df$sociality + df$trend))

summary(lm(priceMcount ~ df$trend))



summary(lm(log(priceMcount) ~ df$weightVariety + df$weightTaste + df$weightPrice + df$weightBrand + df$weightAtmosphere))

summary(lm(log(priceMcount) ~ df$weightTaste + df$weightPrice + df$weightBrand + df$weightAtmosphere))

summary(lm(log(priceMcount) ~ df$weightTaste + df$weightBrand + df$weightAtmosphere))

summary(lm(log(priceMcount) ~ df$weightBrand + df$weightAtmosphere))

summary(lm(priceMcount ~ df$weightBrand))

par(mfrow= c(1,1))
plot(df$weightBrand,priceMcount)
abline(lm(priceMcount ~ df$weightBrand)) # Starbucks가 잘되는 이유 . The reason why starbucks is gathering big money.

summary(lm(priceMcount ~ df$income))
plot(df$income, priceMcount)
abline(lm(priceMcount ~ df$income)) # Starbucks가 잘되는 이유 . The reason why starbucks is gathering big money.

##############################################################################################################3
k.max <- 6
wss <- sapply(1:k.max, function(k){kmeans(df[,c("weightTaste","weightPrice",
        "weightBrand","weightAtmosphere","weightVariety")], k, nstart=10)$tot.withinss})
plot(1:k.max, wss,
     type="b", pch = 19, frame = FALSE, 
     xlab="Number of clusters K",
     ylab="Total within-clusters sum of squares")
abline(v = 3, lty =2)

length(df$weightBrand[df$cluster==1])
length(df$weightBrand[df$cluster==2])
length(df$weightBrand[df$cluster==3])

# change "data -> df" ALL
#0) check independence of them.
head(df)
check_k_means <- kmeans(df[,c("weightTaste","weightPrice",
                              "weightBrand","weightAtmosphere","weightVariety")],3)
cluster_weight = check_k_means$cluster
df <- cbind(df, cluster_weight)
head(df)


###############################################33
par(mfrow=c(3,4))
hist(df$consumePerWeek[df$cluster_weight == 1] * df$rationalPrice[df$cluster_weight == 1]) # cost to buy coffee per week

hist(df$consumePerWeek[df$cluster_weight == 1]) 
hist(df$rationalPrice[df$cluster_weight == 1]) # cost to buy coffee per week
hist(df$weightTaste[df$cluster_weight == 1])
hist(df$weightPrice[df$cluster_weight == 1])
hist(df$weightBrand[df$cluster_weight == 1])
hist(df$weightAtmosphere[df$cluster_weight == 1])
hist(df$weightVariety[df$cluster_weight == 1])
hist(df$taste[df$cluster_weight == 1])
hist(df$saving[df$cluster_weight == 1])
hist(df$health[df$cluster_weight == 1])
hist(df$cultural[df$cluster_weight == 1])
hist(df$sociality[df$cluster_weight == 1])
hist(df$trend[df$cluster_weight == 1])

hist(df$consumePerWeek[df$cluster_weight == 2] * df$rationalPrice[df$cluster_weight == 2]) # cost to buy coffee per week
hist(df$consumePerWeek[df$cluster_weight == 2]) 
hist(df$rationalPrice[df$cluster_weight == 2]) # cost to buy coffee per week
hist(df$weightTaste[df$cluster_weight == 2])
hist(df$weightPrice[df$cluster_weight == 2])
hist(df$weightBrand[df$cluster_weight == 2])
hist(df$weightAtmosphere[df$cluster_weight == 2])
hist(df$weightVariety[df$cluster_weight == 2])
hist(df$taste[df$cluster_weight == 2])
hist(df$saving[df$cluster_weight == 2])
hist(df$health[df$cluster_weight == 2])
hist(df$cultural[df$cluster_weight == 2])
hist(df$sociality[df$cluster_weight == 2])
hist(df$trend[df$cluster_weight == 2])

hist(df$consumePerWeek[df$cluster_weight == 3] * df$rationalPrice[df$cluster_weight == 3]) # cost to buy coffee per week
hist(df$consumePerWeek[df$cluster_weight == 3]) 
hist(df$rationalPrice[df$cluster_weight == 3]) # cost to buy coffee per week
hist(df$weightTaste[df$cluster_weight == 3])
hist(df$weightPrice[df$cluster_weight == 3])
hist(df$weightBrand[df$cluster_weight == 3])
hist(df$weightAtmosphere[df$cluster_weight == 3])
hist(df$weightVariety[df$cluster_weight == 3])
hist(df$taste[df$cluster_weight == 3])
hist(df$saving[df$cluster_weight == 3])
hist(df$health[df$cluster_weight == 3])
hist(df$cultural[df$cluster_weight == 3])
hist(df$sociality[df$cluster_weight == 3])
hist(df$trend[df$cluster_weight == 3])

df[df$cluster_weight == 3,]
hist(df$consumePerWeek[df$cluster_weight == 1]) # count to buy coffee per week
hist(df$consumePerWeek[df$cluster_weight == 2]) # count to buy coffee per week
hist(df$consumePerWeek[df$cluster_weight == 3]) # count to buy coffee per week
hist(df$rationalPrice[df$cluster_weight == 1]) # cost to buy coffee per week
hist(df$rationalPrice[df$cluster_weight == 2]) # cost to buy coffee per week
hist(df$rationalPrice[df$cluster_weight == 3]) # cost to buy coffee per week
mean(df$rationalPrice[df$cluster_weight == 1])
mean(df$rationalPrice[df$cluster_weight == 2])
mean(df$rationalPrice[df$cluster_weight == 3])

length(df$weightBrand[df$cluster_weight==1])
length(df$weightBrand[df$cluster_weight==2])
length(df$weightBrand[df$cluster_weight==3])

#shapiro.test -> 1) check noramlity -> if It is not match independence, use kruskal
shapiro.test(df$weightBrand[df$cluster_weight==1])
shapiro.test(df$weightBrand[df$cluster_weight==2])
shapiro.test(df$weightBrand[df$cluster_weight==3])

par(mfrow = c(2,2))
hist(df$weightBrand[df$cluster_weight==1])
hist(df$weightBrand[df$cluster_weight==2])
hist(df$weightBrand[df$cluster_weight==3])
kruskal.test(df$weightBrand ~ df$cluster_weight, data = df)

#wilcox test
wilcox.test( df$weightBrand[df$cluster_weight==1], 
             df$weightBrand[df$cluster_weight==2], data=df, paired=F)
wilcox.test( df$weightBrand[df$cluster_weight==1], 
             df$weightBrand[df$cluster_weight==3], data=df, paired=F)
wilcox.test( df$weightBrand[df$cluster_weight==2], 
             df$weightBrand[df$cluster_weight==3], data=df, paired=F)

mean(df$weightBrand[df$cluster_weight==1])
mean(df$weightBrand[df$cluster_weight==2])
mean(df$weightBrand[df$cluster_weight==3])

mean(df$consumePerWeek[df$cluster_weight==1] * df$rationalPrice[df$cluster_weight==1])
mean(df$consumePerWeek[df$cluster_weight==2] * df$rationalPrice[df$cluster_weight==2])
mean(df$consumePerWeek[df$cluster_weight==3] * df$rationalPrice[df$cluster_weight==3])

sum(df$consumePerWeek[df$cluster_weight==1] * df$rationalPrice[df$cluster_weight==1])
sum(df$consumePerWeek[df$cluster_weight==2] * df$rationalPrice[df$cluster_weight==2])
sum(df$consumePerWeek[df$cluster_weight==3] * df$rationalPrice[df$cluster_weight==3])
length(df$consumePerWeek[cluster_weight==1])
length(df$consumePerWeek[cluster_weight==2])
length(df$consumePerWeek[cluster_weight==3])

# low & mideum price -> need to high rotation rate. cuz it has a lots of people. Take out strategy is optimal.

head(df)

kruskal.test(df$weightAtmosphere ~ df$cluster_weight, data = df)


hist(df$weightAtmosphere[df$cluster_weight==1])
hist(df$weightAtmosphere[df$cluster_weight==2])
hist(df$weightAtmosphere[df$cluster_weight==3])

t.test(df$weightAtmosphere[df$cluster_weight==1], df$weightAtmosphere[df$cluster_weight==2], var.equal=F)
t.test(df$weightAtmosphere[df$cluster_weight==1], df$weightAtmosphere[df$cluster_weight==3], var.equal=F)
t.test(df$weightAtmosphere[df$cluster_weight==2], df$weightAtmosphere[df$cluster_weight==3], var.equal=F)

#####################################
length(df[df$cluster_weight==3 & df$rationalPrice ==1500,])
length(df[df$cluster_weight==3 & df$rationalPrice ==2500,])
length(df[df$cluster_weight==3 & df$rationalPrice ==1500, "data.id"])
length(df[df$cluster_weight==3 & df$rationalPrice ==2500, "data.id"])
length(df[df$cluster_weight==3 & df$rationalPrice ==3500, "data.id"])

par(mfrow=c(2,2))
hist(df$consumePerWeek)
hist(df[df$cluster_weight==3 & df$rationalPrice ==1500, "consumePerWeek"])
hist(df[df$cluster_weight==3 & df$rationalPrice ==2500, "consumePerWeek"])
hist(df[df$cluster_weight==3 & df$rationalPrice ==3500, "consumePerWeek"])
df[df$cluster_weight==3 & df$consumePerWeek ==3500, "consumePerWeek"]

mean(df[df$cluster_weight==3 & df$rationalPrice ==1500, "consumePerWeek"] * df[df$cluster_weight==3 & df$rationalPrice ==1500, "rationalPrice"])
mean(df[df$cluster_weight==3 & df$rationalPrice ==2500, "consumePerWeek"] * df[df$cluster_weight==3 & df$rationalPrice ==2500, "rationalPrice"])
mean(df[df$cluster_weight==3 & df$rationalPrice ==3500, "consumePerWeek"] * df[df$cluster_weight==3 & df$rationalPrice ==3500, "rationalPrice"])
df[df$cluster_weight==3 & df$rationalPrice ==3500, "data.id"]



wilcox.test( df[df$cluster_weight==3 & df$rationalPrice ==1500, "consumePerWeek"] * df[df$cluster_weight==3 & df$rationalPrice ==1500, "rationalPrice"], 
             df[df$cluster_weight==3 & df$rationalPrice ==2500, "consumePerWeek"] * df[df$cluster_weight==3 & df$rationalPrice ==2500, "rationalPrice"], data=df, paired=F)
wilcox.test( df[df$cluster_weight==3 & df$rationalPrice ==2500, "consumePerWeek"] * df[df$cluster_weight==3 & df$rationalPrice ==1500, "rationalPrice"], 
             df[df$cluster_weight==3 & df$rationalPrice ==3500, "consumePerWeek"] * df[df$cluster_weight==3 & df$rationalPrice ==2500, "rationalPrice"], data=df, paired=F)
wilcox.test( df[df$cluster_weight==3 & df$rationalPrice ==1500, "consumePerWeek"] * df[df$cluster_weight==3 & df$rationalPrice ==1500, "rationalPrice"], 
             df[df$cluster_weight==3 & df$rationalPrice ==3500, "consumePerWeek"] * df[df$cluster_weight==3 & df$rationalPrice ==2500, "rationalPrice"], data=df, paired=F)

############################3


































##########################################3
check_k_means <- kmeans(df[,c("taste","saving","cultural","sociality","trend")],2)
check_k_means

head(check_k_means)
check_k_means$cluster
cluster2 = check_k_means$cluster
# 4.data에 cluster result bind.
class(data)
df <- cbind(df, cluster2)

length(df$weightBrand[df$cluster2==1])
length(df$weightBrand[df$cluster2==2])

shapiro.test(df$weightBrand[df$cluster2==1])
shapiro.test(df$weightBrand[df$cluster2==2])

hist(df$weightBrand[df$cluster2==1])
hist(df$weightBrand[df$cluster2==2])

var.test(df$weightBrand[df$cluster2==1],df$weightBrand[df$cluster2==2])
var.test()
t.test(df$weightBrand[df$cluster2==1],df$weightBrand[df$cluster2==2],var.equal=F)

# p-value is less than 0.05. It means the variance of two is different.

df








##################################33


# 5.2) check the same variance. + I think I should check other prerequisites.
bartlett.test(data$w1~data$cluster, data=data)
# it is bigger than 0.05. So, It could be said fit the same variance.

# 6.Try ANOVA test of lifestyle survey columns. #if they have same variance : anova test. If they have different variance : welch test.
aov.w1 <- aov(data$w1 ~ data$cluster, data = data)
aov.w1
summary(aov.w1)
# It means there is difference between clusters.

# 7. Check the mean of clusters to find the priority.
mean(data$w1[data$cluster == "1"])
mean(data$w1[data$cluster == "2"])
mean(data$w1[data$cluster == "3"])

#7-2. use t.test to check the priority of each cluster (mean) is valid.



# 8. Find the chracteristics of each clusters using above difference of mean.


# 9. Check the same distribution && Try ANOVA test of coffee_buying_count, weight, age, income etc...

#10. Multiple variable Regression.
##
library(ggplot2)
install.packages("GGally")
library(GGally)
pairplot(data)
ggpairs(data[,c(26:30)])
head(data[,c(26:30)])
##

#Reticulate -> It makes R use Python packages
#install.packages('reticulate')
library("reticulate")
sns <- import('seaborn')
plt <- import('matplotlib.pyplot')
pd <- import('pandas')
sm <- import("statsmodels.api")

#df <- data
head(df)
#r_to_py : convert R objects into Python objects. R dataframe is converted into a Python Pandas Dataframe
df
sns$pairplot(r_to_py(df[,c("weightTaste","weightPrice","weightBrand","weightAtmosphere","weightVariety")]), diag_kind="kde")
corrmat = r_to_py(df[,c("weightTaste","weightPrice","weightBrand","weightAtmosphere","weightVariety")])
corrmat = r_to_py(df[c("weightTaste","weightPrice","weightBrand","weightAtmosphere","weightVariety","taste","saving","cultural","sociality","trend")])
corrmat = corrmat$corr()
sns$heatmap(corrmat, cbar=T)
plt$show()
##
model = sm$OLS(r_to_py(df[,"coffee_consume"]),r_to_py(df[,26:30]))
result = model$fit()
print(result$summary())
##
#using r function
data[,"coffee_consume"]
summary(lm(data[,"coffee_consume"] ~ data$w1 + data$w2 + data$w3 + data$w4 + data$w5))
