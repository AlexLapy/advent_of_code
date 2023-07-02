object helper {

    fun matrixToString(matrix: Array<IntArray>): String {
        val numRows = matrix.size
        val numCols = matrix[0].size

        val sb = StringBuilder()

        for (row in 0 until numRows) {
            for (col in 0 until numCols) {
                sb.append(matrix[row][col])
                if (col < numCols - 1) {
                    sb.append(", ")
                }
            }
            if (row < numRows - 1) {
                sb.append("\n")
            }
        }

        return sb.toString()
    }
}