#!/usr/bin/env python3

def NaturalRootedNumbers(number):
    """
    :type number: int
    :rtype: bool
    """

    # Алгоритм перевірки буде полягати в наступному

    # Піднесемо число до квадрату та видалемо його з нього.
    #   в такому разі нам буде відомо чи кратне воно 10
    #   (це число ми будемо перевіряти на етапі 2)

    base = (number**2) - number;
    if base % 10 != 0:
        return False;

    # Знайдемо розряд числа що ми шукаємо
    i = 0;
    while number % ( 10 ** i ) != number:
        i += 1;

    # і перевіримо оcтачу від ділення
    # різниці квадрату нашого числа і нашого числа
    if base % 10**i != 0:
        return False

    return True


# Test Cases
if __name__ == "__main__":

    testCaseList = [
        { 'number': 1, 'expected' : True },
        { 'number': 4, 'expected' : False },
        { 'number': 5, 'expected' : True },
        { 'number': 16, 'expected' : False },
        { 'number': 25, 'expected' : True },
        { 'number': 10, 'expected' : False },
    ]

    messageError = "\033[1;101;30m ( Failed ) \033[0;101;30m {0} \033[0m"
    messageOK    = "\033[1;102;30m ( Passed ) \033[0;102;30m {0} \033[0m"
    message = [
        "{} isn't matching last numbers it's root {}",
        "{} is matching last numbers it's root {}"
    ]


    for testCase in testCaseList :

        testCaseActualResult = NaturalRootedNumbers( testCase.get('number') )

        if testCase.get('expected') == testCaseActualResult :
            print( messageOK.format(    message[testCaseActualResult].format( testCase.get('number'), testCase.get('number')**2 ) ) )
        else:
            print( messageError.format( message[testCaseActualResult].format( testCase.get('number'), testCase.get('number')**2 ) ) )
