f1 = 1234.5678
f2 = 0.33

def div(f1, f2):
    f2_obr = obr(f2)
    return f1*f2_obr

def obr(f):
    t = 1
    step = None

    # Поиск максимального непревышающего
    if f < 1.0:
        flag = 1
        step = 2.0
    else:
        flag = 0
        step = 0.5
    
    # Сам поиск
    while True:
        new = t * step
        x = new * f
        if flag and x > 1:
            break
        elif not flag and x < f:
            t = new
            break
        t = new

    # Итерация
    ret = 0
    chunk = t
    last_chunk = 2*t
    mul_result = 1.0
    while last_chunk - chunk > 0:
        mul = f * chunk
        if mul > mul_result:
            pass
        else:
            mul_result -= mul
            ret += chunk
        
        last_chunk = chunk
        chunk = chunk / 2.0
    return ret


if __name__ == '__main__':
    print('return', obr(0.23459734))
    print('return', obr(2345.9734))
    print('div', f1/f2, div(f1, f2))
