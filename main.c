#include<stdio.h>

// Função para calcular o MDC/ algoritmo de Euclides
int mdc(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Função para o Algoritmo de Euclides Estendido
int euclides_estendido(int a, int b, int *x, int *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    int x1, y1;
    int d = euclides_estendido(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
    return d;
}

// Função para calcular o inverso modular
int inverso_modular(int g, int n) {
    int x, y;
    int d = euclides_estendido(g, n, &x, &y);
    if (d != 1) {
        return -1;
    }
    return (x % n + n) % n;
}
// função para verificar se um número é primo
int primo(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

int teorema_fermat(int n1) {
    if (primo(n1)) {
        int x1 = n1 - 1;
        return x1;
    } else {
        return 0;
    }
}

int totiente(int n1) {
    if (n1 <= 0) return 0;
    int result = n1;
    for (int p = 2; p * p <= n1; p++) {
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

void teorema_divisao(int x, int x1, int *q, int *r) {
    if (x1 == 0) {
        printf("Erro: Divisão por zero em teorema_divisao.\n");
        *q = 0;
        *r = 0;
        return;
    }
    *q = x / x1; // Quociente
    *r = x % x1; // Resto
}

int exp_mod(int base, int exp, int mod) {
    if (mod == 0) {
        printf("Erro: Modulo zero em exp_mod.\n");
        return 0;
    }
    int result = 1;
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
int calcular_expressao(int a, int n1, int x1, int q, int r) {
    int parte1 = exp_mod(a, x1, n1);

    int parte1_q = exp_mod(parte1, q, n1);

    int parte2 = exp_mod(a, r, n1);

    int resultado = (parte1_q * parte2) % n1;

    return resultado;
}



int main() {
    int H, G, n, x, n1;
    int a, x1, q, r, x2;
    printf("Digite o valor de H: ");
    scanf("%d", &H);

    printf("Digite o valor de G: ");
    scanf("%d", &G);

    printf("Digite o valor de n: ");
    scanf("%d", &n);

    printf("Digite o valor de x: ");
    scanf("%d", &x);

    printf("Digite o valor de n1: ");
    scanf("%d", &n1);

    printf("\n--- ETAPA 1: Verificar se G e n são primos ---\n");
    if (mdc(G, n) != 1) {
        printf("%d e %d não são primos entre si.\n", G, n);
        return 0;
    } else {
        printf("%d e %d são primos entre si.\n", H, n);
        printf("\n--- ETAPA 2: Calcular inverso de G em Z_n ---\n");
        int inverso = inverso_modular(G, n);
        if (inverso == -1) {
            printf("O inverso modular não existe.\n");
            return 0;
        } else {
            printf("\n--- ETAPA 3: Calcular a ---\n");
            a = H * inverso % n;
            printf("O inverso modular de %d em relação a %d é: %d\n", G, n, inverso);
            printf("O valor de a é: %d\n", a);
            printf("\n--- ETAPA 4: Verificar se a e n1 são coprimos ---\n");
            if (mdc(a, n1) == 1) {
                printf("%d e %d são coprimos.\n", a, n1); }
            else {
                printf("%d e %d não são coprimos.\n", a, n1);
            }
            printf("\n--- ETAPA 5/6: verifiar se %d é primo e usar o teorema adequado---\n", n1);
            if (primo(n1)) {
                printf("%d é primo. (pequeno teorema de fermat)\n", n1);
                x1 = teorema_fermat(n1);
                teorema_divisao(x, x1, &q, &r);
                printf("Quociente: %d\n", q);
                printf("Resto: %d\n", r);
                int x2 = calcular_expressao(a, n1, x1, q, r);
                int eq1 = calcular_expressao(x2, n1, q, q,r );
                int eq2 = calcular_expressao(a, n1, r, q, r);
                printf("O resultado da primeira expressão é: %d\n", x2);
                printf("O resultado da segunda expressão é: %d\n", eq1);
                printf("O resultado da terceira expressão é: %d\n", eq2);
                int final = (eq1 * eq2) % n1;
                printf("Resultado final: %d\n", final);
            }
            else {
                printf("%d não é primo.(teorema de Euler)\n", n1);
                x1 = totiente(n1);
            teorema_divisao(x, x1, &q, &r);
                printf("Quociente: %d\n", q);
                printf("Resto: %d\n", r);
                int x2 = calcular_expressao(a, n1, x1, q, r);
                int eq1 = calcular_expressao(x2, n1, q, q,r );
                int eq2 = calcular_expressao(a, n1, r, q, r);
                printf("O resultado da primeira expressão é: %d\n", x2);
                printf("O resultado da segunda expressão é: %d\n", eq1);
                printf("O resultado da terceira expressão é: %d\n", eq2);
                int final = (eq1 * eq2) % n1;
                printf("Resultado final: %d\n", final);
            }
        }
    }
}