#include<stdio.h>

// Função para calcular o MDC/ algoritmo de Euclides
long long mdc(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Função para o Algoritmo de Euclides Estendido
long long euclides_estendido(long long a, long long b, long long *x, long long *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    long long x1, y1;
    long long d = euclides_estendido(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
    return d;
}

// Função para calcular o inverso modular
long long inverso_modular(long long g, long long n) {
    long long x, y;
    long long d = euclides_estendido(g, n, &x, &y);
    if (d != 1) {
        return -1;
    }
    return (x % n + n) % n;
}
// função para verificar se um número é primo
long long primo(long long n) {
    if (n <= 1) return 0;
    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

long long teorema_fermat(long long n1) {
    if (primo(n1)) {
        long long x1 = n1 - 1;
        return x1;
    } else {
        return 0;
    }
}

long long totiente(long long n1) {
    if (n1 <= 0) return 0;
    long long result = n1;
    for (long long p = 2; p * p <= n1; p++) {
        if (n1 % p == 0) {
            while (n1 % p == 0) {
                n1 /= p;
            }
            result -= result / p;
        }
    }
    if (n1 > 1) {
        result -= result / n1;
    }
    return result;
}

void teorema_divisao(long long x, long long x1, long long *q, long long *r) {
    if (x1 == 0) {
        printf("Erro: Divisão por zero em teorema_divisao.\n");
        *q = 0;
        *r = 0;
        return;
    }
    *q = x / x1; // Quociente
    *r = x % x1; // Resto
}

long long exp_mod(long long base, long long exp, long long mod) {
    if (mod == 0) {
        printf("Erro: Modulo zero em exp_mod.\n");
        return 0;
    }
    long long result = 1;
    base = base % mod; 

    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp / 2;
        base = (base * base) % mod;
    }
    return result;
}

// Função para calcular a expressão grande
long long calcular_expressao(long long a, long long n1, long long x1, long long q, long long r) {
    long long parte1 = exp_mod(a, x1, n1);

    long long parte1_q = exp_mod(parte1, q, n1);

    long long parte2 = exp_mod(a, r, n1);

    long long resultado = (parte1_q * parte2) % n1;

    return resultado;
}



int main() {
    long long H, G, n, x, n1;
    long long a, x1, q, r, x2;
    printf("Digite o valor de H: ");
    scanf("%lld", &H);

    printf("Digite o valor de G: ");
    scanf("%lld", &G);

    printf("Digite o valor de n: ");
    scanf("%lld", &n);

    printf("Digite o valor de x: ");
    scanf("%lld", &x);

    printf("Digite o valor de n1: ");
    scanf("%lld", &n1);

    printf("\n--- ETAPA 1: Verificar se G e n são primos ---\n");
    if (mdc(G, n) != 1) {
        printf("%lld e %lld não são primos entre si.\n", G, n);
        return 0;
    } else {
        printf("%lld e %lld são primos entre si.\n", G, n);
        printf("\n--- ETAPA 2: Calcular inverso de G em Z_n ---\n");
        long long inverso = inverso_modular(G, n);
        if (inverso == -1) {
            printf("O inverso modular não existe.\n");
            return 0;
        } else {
            printf("\n--- ETAPA 3: Calcular a ---\n");
            a = H * inverso % n;
            printf("O inverso modular de %lld em relação a %lld é: %lld\n", G, n, inverso);
            printf("O valor de a é: %lld\n", a);
            printf("\n--- ETAPA 4: Verificar se a e n1 são coprimos ---\n");
            if (mdc(a, n1) == 1) {
                printf("%lld e %lld são coprimos.\n", a, n1); }
            else {
                printf("%lld e %lld não são coprimos.\n", a, n1);
            }
            printf("\n--- ETAPA 5/6: verifiar se %lld é primo e usar o teorema adequado---\n", n1);
            if (primo(n1)) {
                printf("%lld é primo. (pequeno teorema de fermat)\n", n1);
                x1 = teorema_fermat(n1);
                teorema_divisao(x, x1, &q, &r);
                printf("Quociente: %lld\n", q);
                printf("Resto: %lld\n", r);
                long long x2 = calcular_expressao(a, n1, x1, q, r);
                long long eq1 = calcular_expressao(x2, n1, q, q,r );
                long long eq2 = calcular_expressao(a, n1, r, q, r);
                printf("O resultado da primeira expressão é: %lld\n", x2);
                printf("O resultado da segunda expressão é: %lld\n", eq1);
                printf("O resultado da terceira expressão é: %lld\n", eq2);
                long long final = (eq1 * eq2) % n1;
                printf("Resultado final: %lld\n", final);
            }
            else {
                printf("%lld não é primo.(teorema de Euler)\n", n1);
                x1 = totiente(n1);
            teorema_divisao(x, x1, &q, &r);
                printf("Quociente: %lld\n", q);
                printf("Resto: %lld\n", r);
                long long x2 = calcular_expressao(a, n1, x1, q, r);
                long long eq1 = calcular_expressao(x2, n1, q, q,r );
                long long eq2 = calcular_expressao(a, n1, r, q, r);
                printf("O resultado da primeira expressão é: %lld\n", x2);
                printf("O resultado da segunda expressão é: %lld\n", eq1);
                printf("O resultado da terceira expressão é: %lld\n", eq2);
                long long final = (eq1 * eq2) % n1;
                printf("Resultado final: %lld\n", final);
            }
        }
    }
}