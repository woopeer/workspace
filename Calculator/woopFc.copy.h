#define p(x) printf(x), printf("\n");
#define p2(x, y) printf(x, y), printf("\n");
#define ps(x) printf("%s\n", x);
#define pc(x) printf("%c\n", x);
#define pd(x) printf("%d\n", x);
#define US(x) Uncertain_String(x)
#define ES(x, y) Exchange_String(x, y)
#define EI(x, y) Exchange_Integer(x, y)
#define MS(s1, s2) Multiplication_String(s1, s2)
#define DS(s1, s2) Division_String(s1, s2)
#define PS(s1, s2) Plus_String(s1, s2)
#define MuS(s1, s2) Minus_String(s1, s2)
#define C2I(ch) Char_to_Integer(ch)
#define I2C(in) Integer_to_Char(in)

void Uncertain_String(char **a){
    int len = 0, max_len = 100;
    *a = (char *)malloc(max_len);
    char *b = NULL, c;
    while ((c = getchar()) != '\n'){
        if (len >= max_len){
            max_len *= 2;
            b = realloc(*a, max_len);
            *a = b;
        }
        (*a)[len ++] = c;
    }
    (*a)[len] = '\0';
}

void Exchange_String(char **s1, char **s2){
    char *tmp;
    tmp = *s1;
    *s1 = *s2;
    *s2 = tmp;
}

void Exchange_Integer(int *in1, int *in2){
    int *tmp;
    tmp = *in1;
    *in1 = *in2;
    *in2 = tmp;
}

void Strcpy(char *s1, char **s2, int start, int len){
    if(s1 == NULL) return;
    if(start + len > strlen(s1)) return;
    *s2 = (char *)malloc(len * sizeof(char));
    int i;
    for (i = start; i < len + start; ++ i) {
        (*s2)[i - start] = (s1)[i];
    }
}

char *Strcat(char *s1, char *s2) {
    int len1 = strlen(s1), len2 = strlen(s2);
    char *s = (char *)malloc((len1 + len2 + 1) * sizeof(char));
    int i;
    for (i = 0; i < len1 || i < len2; ++ i){
        if (i < len1) s[i] = s1[i];
        if (i < len2) s[i + len1] = s2[i];
    }
    s[len1 + len2] = '\0';
    return s;
}


void Strcut(char **s1, int start1, char **s2, int start2, int len){
    if(*s1 == NULL) return;
    if(start1 + len > strlen(*s1)) return;
    char *s = (char *)malloc((strlen(*s1) - len) * sizeof(char));
    if(!start2) *s2 = (char *)malloc(len * sizeof(char));
    int i;
    for (i = 0; i < start1; ++ i) {
        s[i] = (*s1)[i];
    }
    for (i = start1; i < start1 + len; ++ i) {
        (*s2)[i - start1 + start2] = (*s1)[i];
    }
    for (i = start1 + len; i < strlen(*s1); ++ i) {
        s[i - len] = (*s1)[i];
    }
    *s1 = s;
}

void Strdsc(char **s, int start, int len, int flag){
    if(*s == NULL || len <= 0) return;
    if(flag && !start){
        *s = *s + len;
        return;
    } else {
        if(start + len > strlen(*s)) return;
    }
    char *s1 = (char *)malloc((strlen(*s) - len) * sizeof(char));
    int i;
    for (i = 0; i < start; ++ i) {
        s1[i] = (*s)[i];
    }
    for (i = start + len; i < strlen(*s); ++ i) {
        s1[i - len] = (*s)[i];
    }
    *s = s1;
}

int Char_to_Integer(char ch){
    if(ch >= '0' && ch <= '9') return ch - '0';
    return -1;
}

char Integer_to_Char(int in){
    if (in >= 0 && in <= 9) return (char)('0' + in);
    return '\0';
}

char *Plus_String(char *s1, char *s2) {
    int sta1 = strlen(s1) - 1, sta2 = strlen(s2) - 1;
    int len = (sta1 > sta2) ? (sta1 + 2) : (sta2 + 2);
    char *s = (char *)malloc(len * sizeof(char));
    int flag = 0, sta = len - 1, end = sta;
    int end1 = (s1[0] == '-') ? (flag ^= 1, 1) : 0, end2 = (s2[0] == '-') ? (flag ^= 1, 1) : 0;
    if (flag) {
        if((sta1 - end1 < sta2 - end2) || (((sta1 - end1 == sta2 - end2)) && s1[end1] < s2[end2])) {
            ES(&s1, &s2);
            EI(&sta1, &sta2);
            EI(&end1, &end2);
        }
        if(end2) flag = 0;
        int carry, idx, minu;
        int i, j, k;
        carry = idx = minu = 0;
        for (i = sta1, j = sta2, k = sta; i >= end1 || j >= end2; -- i, -- j, -- k) {
            minu = C2I((i < end1) ? '0' : s1[i]) - C2I((j < end2) ? '0' : s2[j]) + carry;
            if(minu < 0) carry = -1, minu += 10; //(C2I((i < end1) ? '0' : s1[i]) - C2I((j < end2)? '0' : s2[j])) < 0
            else carry = 0;
            s[k] = I2C(minu);
            -- end;
        }
        if(flag) {
            s[end --] = '-';
        }
        Strdsc(&s, 0, end + 1, 1);
        if (s[1] == '0' && s[0] == '-')
            if (strlen(s) == 2) s = "0";
            else {
                ++ idx;
                for (i = 2; i < strlen(s); ++ i){
                    if(s[i] == '0') ++ idx;
                    else break;
                }
                Strdsc(&s, 1, idx, 0);
            }
        if (s[0] == '0')
            if(strlen(s) != 1){
                ++ idx;
                for (i = 1; i < strlen(s); ++ i){
                    if(s[i] == '0') ++ idx;
                    else break;
                }
                Strdsc(&s, 0, idx, 0);
            }

    } else {
        int carry, base, sum;
        int i, j, k;
        carry = base = sum = 0;
        for (i = sta1, j = sta2, k = sta; i >= end1 || j >= end2; -- i, -- j, -- k) {
            sum = C2I((i < end1) ? '0' : s1[i]) + C2I((j < end2) ? '0' : s2[j]) + carry;
            carry = sum / 10;
            base = sum % 10;
            s[k] = I2C(base);
            -- end;
        }
        if(end1 || end2) {
            s[end --] = '-';
        }
        Strdsc(&s, 0, end + 1, 1);
    }
    return s;
}

char *Plus_String_Fraction(char *s1, char *s2){
    int idxs, idxv, idx, len1 = strlen(s1), len2 = strlen(s2), lens, lenv, lenp, option;
    int i;
    for (i = 0; i < len1; ++ i)
        if(s1[i] == '.') idxs = i;
    for (i = 0; i < len2; ++ i)
        if(s2[i] == '.') idxv = i;
    int flen1 = len1 - idxs - 1, flen2 = len2 - idxv - 1;
    idx = (flen1 > flen2) ? (lens = len1, option = flen1 - flen2, flen1) : (lens = len2, EI(&idxs, &idxv), option = flen2 - flen1, flen2);
    char *sv = (char *)malloc(lens + idx * sizeof(char));
    char *tmp, *s = (lens == len1) ? (tmp = s2, lenp = len2, s1) : (tmp = s1, lenp = len1, s2);
    lenv = lenp + option;
    for (i = 0; i < lenv; ++ i){
        if(i < lenp)
            sv[i] = tmp[i];
        else
            sv[i] = '0';
    }
    Strdsc(&s, idxs, 1, 0);
    Strdsc(&sv, idxv, 1, 0);
    char *sum = PS(s, sv);
    char *fraction = (char *)malloc(idx * sizeof(char));
    idx = strlen(sum) - idx;
    Strcut(&sum, idx, &fraction, 0, strlen(sum) - idx);
    sum = Strcat(Strcat(sum, "."), fraction);
    return sum;
}

char *Minus_String(char *s1, char *s2){
    Check();
    int flag = 0;
    if(s2[0] == '-') flag = 1;
    flag ? Strdsc(&s2, 0, 1, 1) : (s2 = Strcat("-", s2));
    return Plus_String(s1, s2);
}

char *Minus_String_Fraction(char *s1, char *s2){
    int flag = (s2[0] == '-') ? 1 : 0;
    if(flag) Strdsc(&s2, 0, 1, 0);
    else {
        s2 = Strcat("-", s2);
    }
    return Plus_String_Fraction(s1, s2);
}

char *Multiplication_String(char *s1, char *s2) {
    Check();
    int sta1 = strlen(s1) - 1, sta2 = strlen(s2) - 1;
    int len = (sta1 > sta2) ? (sta1 * 2 + 2) : (sta2 * 2 + 2);
    char *s = (char *)malloc(len * sizeof(char));
    int flag = 0, sta = len - 1, end = sta;
    int end1 = (s1[0] == '-') ? (flag ^= 1, 1) : 0, end2 = (s2[0] == '-') ? (flag ^= 1, 1) : 0;
    int carry, base, multi;
    int i, j, idx_x, idx_y;
    carry = base = multi = 0;
    for (i = 0; i < len; ++ i) s[i] = '0';
    for (i = sta1; i >= end1; -- i) {
        carry = 0;
        idx_x = sta1 - i + 1;
        for (j = sta2; j >= end2; -- j) {
            idx_y = sta2 - j + 1;
            int idx = sta - (idx_x + idx_y - 2);
            multi = C2I((i < end1) ? '1' : s1[i]) * C2I((j < end2) ? '1' : s2[j]) + I2C(s[idx]);
            carry = multi / 10 + (C2I(s[idx]) + multi % 10) / 10;
            base = (C2I(s[idx]) + multi % 10) % 10;
            s[idx] = I2C(base);
            while (carry){
                carry += C2I(s[-- idx]);
                base = carry % 10;
                carry /= 10;
                s[idx] = I2C(base);
                if (idx < end) end = idx;
            }
            if (idx < end) end = idx;
        }
    }
    if (flag) s[-- end] = '-';
    Strdsc(&s, 0, end, 1);
    return s;
}

char *Multiplication_String_Fraction(char *s1, char *s2){
    int idxs, idxv, idx, len1 = strlen(s1), len2 = strlen(s2);
    int i, j;
    for (i = 0; i < len1; ++ i)
        if(s1[i] == '.') idxs = i;
    for (i = 0; i < len2; ++ i)
        if(s2[i] == '.') idxv = i;
    int flen1 = len1 - idxs - 1, flen2 = len2 - idxv - 1;
    idx = flen1 + flen2;
    //(flen1 > flen2) ? (lens = len1, option = flen1 - flen2, flen1) : (lens = len2, EI(&idxs, &idxv), option = flen2 - flen1, flen2)
    Strdsc(&s1, idxs, 1, 0);
    Strdsc(&s2, idxv, 1, 0);
    char *multi = Multiplication_String(s1, s2);
    char *fraction = (char *)malloc(idx * sizeof(char));
    idx = strlen(multi) - idx;
    Strcut(&multi, idx, &fraction, 0, strlen(multi) - idx);
    multi = Strcat(Strcat(multi, "."), fraction);
    return multi;
}

char *Lowercase_to_Uppercase(char *s){
    int len = strlen(s);
    char *sv = (char *)malloc(len * sizeof(char));
    int i;
    char ch;
    for (i = 0; i < len; ++ i) {
        if(!((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))) sv[i] = s[i];
        else sv[i] = (s[i] & 32) ? s[i] ^ 32 : s[i];
    }
    return sv;
}

int Check(char *s){
    enum{NOT_VALID, VALID};
    if(s == NULL) return NOT_VALID;
    int i, idx = 0, start = (s[0] == '-') ? 1 : 0, len = strlen(s), cnt;
    if(s[0] == '-' || (s[0] > '0' && s[0] <= '9') || (s[0] == '0' && len == 1));
    else if(s[0] == '+') Strdsc(&s, 0, 1, 0);
    else return NOT_VALID;
    len = strlen(s);
    cnt = 0;
    for (i = start; i < len; ++ i)
        if(s[i] == '.') ++ cnt;
    if(cnt > 1) return NOT_VALID;
    if(cnt) if(s[len - 1] == '.') return NOT_VALID;
    for (i = start; i < len; ++ i)
        if ((s[i] < '0' || s[i] > '9') && s[i] != '.') return NOT_VALID;
    for (i = start; i < strlen(s); ++ i){
        if(s[i] == '0') ++ idx;
    }
    if(idx) Strdsc(&s, start, idx, 1);
    return VALID;
}

int Check_O(char ch){
    enum{NOT_VALID, VALID};
    if (ch == NULL) return NOT_VALID;
    if (ch != '+' && ch != '-' && ch != '*') return NOT_VALID;
    return VALID;
}

/*
void changingSystem(){
    int base;
    char *I, *i;
    US(&I);
    Cenvertor(&I, &i);
    //char *tmp = strcat(changing_I(base), changing_i(base));

}

char *changing_I(int index){
    int t;
    scanf("%d", &t);
    char *b, *o, *s;
    int i, j;
    while(1){
        i = t % 2;
        t = t / 2;
        if(t == 1){
            b = strcat(b, "1");
            break;
        }
        b = strcat(b, (i ? "1" : "0"));
    }
}

char *changing_i(int index){

}

void Cenvertor(char **I, char **i){
    Check();
    int idx, len = strlen(*I), w;
    for (w = 0; w < len; ++ w) {
        if ((*I)[w] == '.')
            idx = w;
    }
    Strcut(&(*I), &(*i), idx, len - idx);
    ps(*I);
    ps(*i);
}
*/
