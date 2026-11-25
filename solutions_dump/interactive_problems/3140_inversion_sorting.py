I=input
n=int(I())
def R(i,j):
    print(i,j)
    x=int(I())
    if x==0:quit()
    return x
s=0
i=1
while i<=n:
    x=i-(s-R(1,i)+R(1,i))//2
    if x<i:
        R(x,i)
        R(x+1,i)
    s+=i
    i+=1
