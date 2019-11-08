#!/usr/bin/env python3

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

b = [176.57808975, -1.28840566, 0.00370311]


def f(x: np.ndarray) -> np.ndarray:
    return b[0] + b[1] * x + b[2] * x**2


def main() -> None:
    ds = pd.read_csv('in.txt')
    plt.scatter(ds.iloc[:, 0], ds.iloc[:, 1])
    print(ds)
    x = np.linspace(0, 200, 1000)
    y = f(x)
    plt.plot(x, y, '--', color='orange', label='Least Squares fit')

    xp = np.array([185])
    yp = f(xp)
    for i in enumerate(xp):
        plt.plot(i[1],
                 yp[i[0]],
                 'x',
                 color='red',
                 label='({}, {})'.format(i[1], yp[i[0]]))

    plt.grid()
    plt.xlabel('Height')
    plt.ylabel('Weight')
    plt.title('Least Square Regression')
    plt.legend()
    plt.show()


if __name__ == '__main__':
    main()
