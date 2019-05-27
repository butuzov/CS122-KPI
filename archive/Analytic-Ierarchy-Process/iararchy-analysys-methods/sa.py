#!/usr/bin/env python3

import numpy as np
import sympy as sp
import pandas as pd
from scipy import linalg

from IPython.display import display, Markdown, Latex,  HTML
from ipywidgets import interact, interactive, fixed, interact_manual
import ipywidgets as widgets

pd.options.display.float_format = '{:,.3f}'.format

from collections import defaultdict
from copy import deepcopy
from abc import abstractmethod

from typing import List, Tuple


class iMatrixMethod(object):
    """interface"""

    @abstractmethod
    def __init__(self, matrix):
        pass

    @abstractmethod
    def result() -> str:
        pass

class Matrix:

    def __init__(self, data, labels):
        """
        Initial creation of matrix based on string data of sympy to repesent
        rational values

        Arguments:
            data {List[Int]} -- Flat list of numbers (represented with strings)
                                that passed to matrix method later. It's suppose to be
                                n * n
            labels {List[str]} -- List of labels for matrix.
        """

        self.length = len(labels)
        self.data   = data
        self.labels = labels
        self.matrix = self.to_matrix()

    def _repr_html_(self) -> str:
        return self.matrix.to_html()

    def to_matrix(self) -> pd.DataFrame:
        """
        Transform list to numpy matrix

        Returns:
            pd.DataFrame -- matrix representation of flat list.
        """

        rational_list = list(map(lambda x: sp.Rational(x), self.data))

        return pd.DataFrame(
            data=np.array(rational_list).reshape(self.length, -1),
            index=self.labels,
            columns=self.labels,
        )

    @staticmethod
    def latex_matrix(m):
        """
        Return useful to LaTeX represetantion matrix data, based on numpy to_latex method.
        """
        return (m.to_latex(index=False).split("\midrule\n")[1]).split("\n\\bottomrule")[0]

class Fusion:
    """ Роутер для обрахунку синтезу """
    def __init__(self, criteries, alternatives):
        self._criteries = criteries.matrix()
        self._alternatives = [x['router'].matrix() for x in alternatives]

        self.columns = self._criteries.labels
        self.indexes = self._alternatives[0].labels

        values = [x.matrix['$w_i$'].values for x in self._alternatives ]
        self.matrix = pd.DataFrame(data=np.array(values).T, columns=self.columns, index=self.indexes)

    def _repr_html_(self):
        return self.matrix.to_html()

### DONE: Weights ############################################################################################

class Weights_AN(iMatrixMethod):
    r"""
    ### Знаходження локальних вaгів методом AN <br/>`Additive Normalization`
    $$w_i =  \dfrac{1}{\sum\limits_{j=1}^n d_{ij}} \qquad i=\overline{1,m} $$
    """
    def __init__(self, matrix: Matrix):
        self.m = matrix
        self.do()

    def do(self):
        v1 = 1 / self.m.matrix[self.m.labels].sum(axis=0)
        self.m.matrix['$w_i$'] =  v1 /  v1.sum()
        self.m.matrix['$v_i^{AN}$'] = v1
        self.m.matrix['$w_i^{AN}$'] = self.m.matrix['$w_i$']


    def result(self) -> str:
        return self.m.matrix.to_html()

class Weights_RGMM(iMatrixMethod):
    r"""
    ### Знаходження локальних вaгів методом RGMM <br> `Row Geometric Mean Method`
    $$w_i = \dfrac{\sqrt[n]{\prod_{j=1}^n a_{ij}}}
    {\sum_{i=1}^{n}{\sqrt[n]{\prod_{j=1}^n a_{ij}}}}$$
    """
    def __init__(self, matrix:Matrix):
        self.m = matrix
        self.do()

    def do(self):
        sqrt_product = self.m.matrix[self.m.labels].prod(axis=1) ** (1 / self.m.length)
        self.m.matrix['$w_i$'] = sqrt_product / sqrt_product.sum()
        self.m.matrix['$w_i^{RGMM}$'] = self.m.matrix['$w_i$']

    def result(self) -> str:
        return self.m.matrix.to_html()

class Weights_EM(iMatrixMethod):
    r"""
    ### Знаходження локальних вaгів методом EM `(Eigenvalue Method)`

    В данному прикладі власне значення матриці - було знайдено за допомогою алгоритмiв реалізованих пакетом [scipy.linalg](https://docs.scipy.org/doc/scipy/reference/generated/scipy.linalg.eig.html#scipy.linalg.eig). Опис деяких алгоритмів доступний на сторінці [`Алгоритм_вычисления_собственных_значений`](https://ru.wikipedia.org/wiki/Алгоритм_вычисления_собственных_значений) у вікіпедії. Для матриці 3x3 застосовуємо простушу формулу.

    $$ D = \begin{pmatrix}
        1   & a   & b \\
        1/a & 1   & c \\
        1/b & 1/c & 1 \\
        \end{pmatrix} \qquad
        w = \begin{pmatrix} \sqrt[3]{ab} \\ \sqrt[3]{\dfrac{a}{c}} \\ \sqrt[3]{\dfrac{1}{bc}} \end{pmatrix}$$

    """
    def __init__(self, matrix):


        self.m  = matrix
        self.do()

    def em(self, epsilon=10e-13):

        matrix = np.atleast_2d(self.m.matrix[self.m.labels].astype(float))

        val, vec = Weights_EM.max_eigh(matrix, norm=lambda x:  x / np.sum(x))

        if np.fabs(np.imag(val)) > epsilon:
            raise TypeError("Invalid import matrix")

        ci = (np.real(val) - self.m.length) / (self.m.length - 1.0)
        vec = np.real(vec)

        # print("CI", ci)

        if (vec >= 0).all():
            return vec

        if (vec <= 0).all():
            return -vec

        raise TypeError("Invalid import matrix")

    @staticmethod
    def max_eigh(matrix, norm=None):
        eigen = linalg.eig(matrix)
        eigh_value, eigh_vector  = eigen[0][0], eigen[1][:, 0]
        return eigh_value, eigh_vector if norm is None else norm(eigh_vector)

    def em3x3(self):
        a = self.m.matrix[self.m.labels].iloc[0,1]
        b = self.m.matrix[self.m.labels].iloc[0,2]
        c = self.m.matrix[self.m.labels].iloc[1,2]
        vector = np.array([a*b, c/a, 1/(b*c)]) ** (1/3)
        return (vector / vector.sum()).astype(float)

    def do(self):
        if self.m.matrix.shape[0] == 3:
            self.m.matrix['$w_i$'] = self.em3x3()
        else:
            self.m.matrix['$w_i$'] = self.em()

        self.m.matrix['$w_i^{EM}$'] = self.m.matrix['$w_i$']

    def result(self) -> str:
        return self.m.matrix.to_html()

### DONE: Consistency ########################################################################################

class Consistency_Ratio(iMatrixMethod):
    r"""
        ### Оцінка узгодженісті матриці парних порівнянь методом CR
        # Оцінка Узгодженості МПП методом CR <br/> `(Consistency Ratio)`

        $$ CR = \dfrac{CI}{MRCI} \qquad CI = \dfrac{\lambda_{max}-n}{n-1} \qquad CI \geqslant 0 $$

        $$
        \begin{cases}
        CR \leqslant .10 & \text{результати вірогідні} \\\\
        CR \geqslant .20 & \text{результати невірогідні і слід переглянути показники} \\\\
        \end{cases}
        $$

        <table>
        <tr><th colspan="15">Порогові значення CR</th></tr>
        <tr><th>1</th><th>2</th><th>3</th><th>4</th><th>5</th><th>6</th><th>7</th><th>8</th><th>9</th><th>10</th><th>11</th><th>12</th><th>13</th><th>14</th><th>15</th></tr>
        <tr><td>0</td><td>0</td><td>0.52</td><td>0.89</td><td>1.11</td><td>1.25</td><td>1.40</td><td>1.45</td><td>1.49</td><td>1.51</td><td>1.52</td><td>1.54</td><td>1.56</td><td>1.58</td><td>1.59</td></tr>
        </table>
    """

    # dss metoichka
    j_e = [.0, .0, 0.52, 0.89, 1.11, 1.25, 1.35, 1.40, 1.45, 1.49, 1.52, 1.54, 1.56, 1.58, 1.59]
    # saati
    # j_e = [.0, .0, 0.58, 0.9, 1.12, 1.24, 1.32, 1.41, 1.45, 1.49, 1.51, 1.54, 1.56, 1.57, 1.59]

    " presiosion "
    pres = 3

    def __init__(self, matrix):
        self.m = matrix

    def result(self):
        nn = "\n\n"

        return ( self.lmbd() + nn + self.lmbd_max() + nn + self.ci() + nn + self.cr() )

    def lmbd(self):
        self.m.matrix["$\lambda$"] = (np.dot(self.m.matrix[self.m.labels], self.m.matrix["$w_i$"])).astype(float)

        A = Matrix.latex_matrix(self.m.matrix[self.m.labels])
        w = Matrix.latex_matrix(self.m.matrix[["$w_i$"]])
        lmbd = Matrix.latex_matrix(self.m.matrix[["$\lambda$"]])

        return ("$$" fr"\lambda = A \times w = \begin{{pmatrix}} {A} \end{{pmatrix}} \times "
                fr"\begin{{pmatrix}} {w} \end{{pmatrix}} =  \begin{{pmatrix}} {lmbd} \end{{pmatrix}}" "$$" )


    def lmbd_max(self):
        self.lambda_max = (self.m.matrix["$\lambda$"]  / self.m.matrix["$w_i$"] ).sum() / self.m.length

        vector_1_str = "+".join(list(map(lambda x: f"\dfrac{{{x[0]:,.{self.pres}f}}}{{{x[1]:,.{self.pres}f}}}",
            zip(self.m.matrix["$\lambda$"] , self.m.matrix["$w_i$"])
        )))
        vector_2_str = "+".join(list(map(lambda x: f"{x:,.{self.pres}f}",
            self.m.matrix["$\lambda$"] / self.m.matrix["$w_i$"]
        )))

        return ("$$ \lambda_{max}"
                fr" \dfrac{{\sum_{{i=1}}^n \dfrac{{\lambda_i}}{{w_i}}}}{{n}} = "
                fr" \dfrac{{{vector_1_str}}}{{{self.m.length}}} = "
                fr" \dfrac{{{vector_2_str}}}{{{self.m.length}}} = "
                f" {self.lambda_max:,.{self.pres}f}"
                "$$")

    def ci(self):
        self.ci_ = (self.lambda_max - self.m.length) / (self.m.length - 1)

        self.ci_ = self.ci_ if self.ci_ > 0 else -self.ci_



        return (
            "$$CI = \dfrac{\lambda_{max}-n}{n-1} = "
            f"\dfrac{{ {self.lambda_max:,.{self.pres}f} - {self.m.length} }}{{{self.m.length - 1}}} = {self.ci_:,.{self.pres}f}"
            "$$"
        )

    def cr(self):

        self.jc = self.j_e[self.m.length-1]
        self.cr = self.ci_ / self.jc

        return  f"$$CR = \dfrac{{CI}}{{MRCI}} = \dfrac{{ {self.ci_:,.{self.pres}f} }}{{ {self.jc } }} = {self.cr:,.{self.pres}f}$$"


class HCRI():
    _instance = None
    _hrci = {}
    itterations = 100

    def __new__(class_, *args, **kwargs):
        if not isinstance(class_._instance, class_):
            class_._instance = object.__new__(class_, *args, **kwargs)
        return class_._instance

    def generate(self, size):
        return np.array([self.calculate_hci(self.random_matrix(size)) for x in range(self.itterations)]).mean()

    def random_matrix(self, size):
        res = np.triu(np.random.randint(-9, 10, (size, size)), 1).astype(float)

        res[res < 0]  = 1 / abs(res[res < 0])
        # res[res == 0] = 1
        res += np.identity(size)

        for i in range(size):
            for j in range(i+1, size):
                if res[i,j] != 0:
                    res[j,i] = 1/res[i,j]
        return res

    def mean(self, size:int):
        if self._hrci.get(size, None) != None:
            return self._hrci[size]

        self._hrci[size] = self.generate(size)
        return self._hrci[size]

    def hmean(self, row):
        return len(row) / (1/row).sum()

    def calculate_hci(self, mat):
        s_j = mat.sum(axis=0)
        hm = self.hmean(s_j)
        n = len(s_j)
        return (hm - n) * (n + 1) / n / (n - 1)

class Harmonic_Consistency_Ratio:
    r"""
    $$HCI(n) = \dfrac{(HM(s)-n)(n+1)}{n(n-1)}$$

    Де $HM(s)=n \left(\sum\limits_{j=1}^n s_j^{-1} \right)^{-1}$ - гармонічне середнє.

    Гармнонічним відношенням узгодженості (harmonic consistency relation) називається

    $$ HCR(n) = \frac{HCI(n)}{HRCI(n)} $$

    де $HRCI(n)$ – середнє значення $HCI(n)$ для випадкових МПП.

    <table>
    <tr><th colspan="3">Порогове значення HCR</th></tr>
    <tr><th>n=3</th><th>n=4</th><th>n>=5</th></tr>
    <tr><td>0.05</td><td>0.08</td><td>0.1</td></tr>
    </table>
    """

    " presiosion "
    pres = 5

    def __init__(self, matrix):
        self.m  = matrix

    def hm(self) -> str:
        self.s_j     = Harmonic_Consistency_Ratio.calc_hm_s(self.m.matrix[self.m.labels])
        self.s_j_1   = Harmonic_Consistency_Ratio.calc_hm_sj(self.s_j)
        self.hmean   = Harmonic_Consistency_Ratio.calc_hm_mean(self.m.length, self.s_j_1.sum())

        frac_str = "+".join(list(map( lambda x: f"\dfrac{{1}}{{{x:,.{self.pres}f}}}", self.s_j)))
        frac_sum_str = self.s_j_1.sum()

        return ( "$$"
            f"HM = \dfrac{{{self.m.length}}}{{ \sum\limits_{{i=1}}^m \dfrac{{1}}{{ \sum\limits_{{j=1}}^n d_{{ij}}  }}}} = "
            f"\dfrac{{{self.m.length}}}{{ {frac_str} }} = \dfrac{{{self.m.length}}}{{ {frac_sum_str:,.{self.pres}f} }} = {self.hmean:,.{self.pres}f}"
        "$$")


    @staticmethod
    def calc_hm_s(matrix):
        return matrix.sum(axis=0)

    @staticmethod
    def calc_hm_sj(vector):
        return 1/vector

    @staticmethod
    def calc_hm_mean(n, m):
        return n/m

    @staticmethod
    def calc_hci(hmean, n):
        return ((hmean-n)*(n+1))/(n*(n-1))


    def hcri(self):

        self._hcri = HCRI().mean(self.m.length)

        return ("$$"
            f" HRCI({self.m.length}) = {self._hcri:,.{self.pres}f}"
        "$$")

    def hci(self) -> str:
        length = self.m.length
        self._hci = Harmonic_Consistency_Ratio.calc_hci(self.hmean, self.m.length)

        return ( "$$"
            f"HCI = \dfrac{{({self.hmean:,.{self.pres}f}-{length})({length}+1)}}"
            f"{{{length} ({length}-1)}} = {self._hci:,.{self.pres}f}"
        "$$")

    def hcr(self) -> str:
        self._hcr = self._hci / self._hcri
        return ("$$"
            "HCR = \dfrac{HCI}{HCRI} ="
            f"\dfrac{{{self._hci:,.{self.pres}f}}}{{{self._hcri:,.{self.pres}f}}} "
            f"= {self._hcr:,.{self.pres}f}"
        "$$")

    def result(self) -> str:
        nn = "\n\n"
        return (self.hm() + nn + self.hci() + nn + self.hcri() + nn + self.hcr() )


class Geometric_Consistency_Index:
    r"""
    # Оцінка Узгодженості МПП методом GCI <br/> `(Geometric Consistency Index)`
    $$ GCI=\frac{2}{(n-1)(n-2)} \sum\limits_{i < j} \log ^2 e_{ij} $$

    Де: $e_{ij}=d_{ij} \frac{v_j}{v_i}$, $v_i = \sqrt[n]{\prod\limits_{j=1}^{n} d_{ij}}$

    <table>
    <tr><th colspan="3">Порогові значення GCI</th></tr>
    <tr><th>n=3</th><th>n=4</th><th>n=5</th></tr>
    <tr><td>0.1573</td><td>0.3526</td><td>0.370</td></tr>
    </table>
    """

    " presiosion "
    pres = 5

    def __init__(self, matrix):
        self.m = matrix

        self.do()

    def do(self):
        #
        v = (self.m.matrix[self.m.labels].prod(axis=1) ** (1/self.m.length)).values
        n = self.m.length

        # e_ij matrix (trianlge)
        e_ij_f = np.tril(self.m.matrix[self.m.labels] * (  v/ v[:, None]), -1)
        e_ij_s = e_ij_f[e_ij_f != 0].astype(float)

        self.gci = (2 * (np.log(e_ij_s)** 2).sum() ) / ((n-1)*(n-2))

    def result(self):
        return  f"$$ GCI({self.m.length}) = {self.gci:,.{self.pres}f} $$"

### DONE: Fusion ################################################################################################

class Fusion_Distributive(iMatrixMethod):
    r"""
    ### Дистрибутивний метод синтезу
    $$
    w_{i}^{global} = \sum_{j=1}^M  w^C_j r_{ij}
    $$
    Де
    $$ r_{ij} = \dfrac{a_{ij}}{\sum_{k=1}^N a_{kj}}$$
    Де $j$ це критерії $j=\overline{1,M}$, а $i$ це альтернативи $i=\overline{1,N}$
    """
    def __init__(self, matrix):
        self.m = matrix
        self.do()

    def do(self):

        v_ij = self.m.matrix[self.m.columns].values * self.m._criteries.matrix['$w_i$'].values
        self.m.matrix['$w^{DIST}$'] =  v_ij.sum(axis=1) / v_ij.sum(axis=1).sum()

    def result(self) -> str:
        return self.m.matrix.to_html()

class Fusion_Multyplicative(iMatrixMethod):
    r"""
    ### Мультиплікативний метод синтезу
    $$
    w_{i}^{global} = \dfrac{\prod_{j=1}^M r_{ij}^{w^C_j}}{\sum_{i=1}^N {\prod_{j=1}^M r_{ij}^{w^C_j} }} \\
    $$

    ---

    Де $j$ це критерії $j=\overline{1,M}$, а $i$ це альтернативи $i=\overline{1,N}$
    """
    def __init__(self, matrix):
        self.m = matrix



        self.do()

    def do(self):
        # old
        # w = [(x ** self.m._criteries.matrix['$w_i$'].values).prod() for x in self.m.matrix[self.m.columns].values]
        # self.m.matrix['$w_i$'] =  w / sum(w)

        v_ij = self.m.matrix[self.m.columns].values ** self.m._criteries.matrix['$w_i$'].values
        self.m.matrix['$w^{MULTY}$'] =  v_ij.prod(axis=1) / v_ij.prod(axis=1).sum()


    def result(self) -> str:
        return self.m.matrix.to_html()



class Fusion_Ideal(iMatrixMethod):
    """
    ### Ідеальний метод синтезу
    $$r_{ij} = \frac{w_{ij}}{\max\limits_{i=\overline{1,n}}{w_{ij}}} \quad v_i^{glob}=\sum\limits_{j=1}^m r_{ij} w_j^C$$
    $$w_j^{glob} = \frac{v_i^{glob}}{\sum\limits_{i=1}^n v_{i}^{glob}}$$
    """

    def __init__(self, matrix):
        self.m = matrix
        self.do()

    def do(self):
        matrix = self.m.matrix[self.m.columns].values
        weights = self.m._criteries.matrix['$w_i$'].values

        r_ij = matrix / matrix.max(axis=0)


        v_ij = r_ij * weights


        self.m.matrix['$w^{IDEAL}$'] = v_ij.sum(axis=1) / v_ij.sum(axis=1).sum()

    def result(self) -> str:
        return self.m.matrix.to_html()

### TODO ########################################################################################################

### DONE: Router ###############################################################################################



class Router:

    _methods = dict()

    def __init__(self, matrix: Matrix):

        self._matrix = matrix

        self._methods['weights'] = dict()
        self._methods['weights']['EM']   = Weights_EM
        self._methods['weights']['AN']   = Weights_AN
        self._methods['weights']['RGMM'] = Weights_RGMM

        self._methods['indexes'] = dict()
        self._methods['indexes']['GCI'] = Geometric_Consistency_Index
        self._methods['indexes']['HCR'] = Harmonic_Consistency_Ratio
        self._methods['indexes']['CR']  = Consistency_Ratio

        self._methods['fusions'] = dict()
        self._methods['fusions']['Distributive']   = Fusion_Distributive
        self._methods['fusions']['Multyplicative'] = Fusion_Multyplicative
        self._methods['fusions']['Ideal']   = Fusion_Ideal




    def matrix(self) -> Matrix:
        return self._matrix

    def _route(self, methods_type:str, method: str) -> Tuple[Markdown, Markdown]:

        if self._methods.get(methods_type, None) == None:
            raise Exception( f"Unknown Method Type [{methods_type}]" )

        if self._methods[methods_type].get(method, None) == None:
            raise Exception( f"Unknown *{methods_type}* Method [{method}]" )

        method = self._methods[methods_type][method]

        return (
            Markdown( "\n".join(list(map( lambda x: x.strip(),  method.__doc__.split("\n")))) ), # Docstring - method
            Markdown( method( self._matrix ).result() ),                                                 # Actual output
        )


    def list_methods(self, methods_type) -> List:

        if self._methods.get(methods_type, None) == None:
            raise Exception( f"Unknown Methods Type [{methods_type}]" )

        return list(self._methods[methods_type].keys())

    def fusion(self, method) -> Tuple[Markdown, Markdown]:
        return self._route( 'fusions', method)

    def weight(self, method) -> Tuple[Markdown, Markdown]:
        return self._route( 'weights', method)

    def index(self, method) -> Tuple[Markdown, Markdown]:
        return self._route( 'indexes', method)
