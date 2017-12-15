#!/usr/bin/env python3
#!/
if __name__ == '__main__':

    list_Of_Lists = [
        [ 1, -1, -1],
        [-1, 1, 2],
        [1, -2, 1]
    ]
    print(list_Of_Lists)

    for row in range(1,4):
        for col in range(1,4):
            matrix  = "\\begin{bmatrix}";

            k = 0;
            m = [[0,0],[0,0]];
            for i in range(0,3):
                for j in range(0,3):
                    if (i+1) != row and (j+1) != col:

                        m[ int(k/2) ][ k%2 ] = list_Of_Lists[i][j];
                        k+=1

                        # matrix += str(list_Of_Lists[i][j])
                        # matrix += "&"

                    # matrix += " \\\\ ";

        # //    print(m)
            matrix += f"{m[0][0]}&{m[0][1]}\\\\{m[1][0]}&{m[1][1]}"
            matrix += " \end{bmatrix}";
            print( f"\\begin{{array}}{{lllll}}S_{{{row}{col}}} = & (-1)^{{{row}+{col}}} & {matrix} & = (-1)^{{{row}+{col}}}(({m[0][0]} \cdot {m[1][1]})-({m[0][1]} \cdot {m[1][0]}) = \\end{{array}}" )
