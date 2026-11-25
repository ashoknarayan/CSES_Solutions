from decimal import Decimal, getcontext

# Set precision high enough
getcontext().prec = 50

def main():
    n, k = map(int, input().split())
    
    ans = Decimal(0)
    
    # Perform the calculations with Decimal to avoid precision issues
    for i in range(1, k + 1):
        add = Decimal(1)
        sub = Decimal(1)
        
        for j in range(1, n + 1):
            add *= Decimal(i) / Decimal(k)
            sub *= Decimal(i - 1) / Decimal(k)
        
        ans += Decimal(i) * (add - sub)
    
    # Printing with precision 6 after decimal
    print(f"{ans:.6f}")

if __name__ == "__main__":
    main()
