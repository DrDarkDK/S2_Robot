# Documentation
Please try to keep this up to date. That way no functions will get lost, as the program grows bigger.
``` ```
## Global

```std::vector<int> getCursorPosition(sf::RenderWindow &window)```
As the name suggests, this function gets the cursor's position **compared to the window**; not the full screen itself.
The cursor's position is returned as a small vector with integers between 1 and 8, exactly as the chessboard's grid.

```void createPiece(std::string type, bool isWhite, sf::Texture& texture, std::vector<int> position, ChessBoard& board, std::vector<std::shared_ptr<ChessPiece>>& pieces)```
The top-lay function to handle the creation of chess pieces. It's a collection of smaller segments that together handle "everything".

```std::vector<float> coordsToPosition(std::vector<float> position)```
Will modify a set of coordinates slightly, so they are placed correctly when visualized.

```std::shared_ptr<ChessPiece> addChessPiece(ChessBoard& board, ChessPiece& piece, std::vector<int> position)```
This function will "create" a new chess piece, on the given board, by the given position. This is useful for creating the start layout.
This function does NOT create the ChessPiece object. The function however accepts the ChessPiece object as a parameter, and will convert it into a pointer.

After this function has been used on an object, the original object shouldn't be used anymore. Use the pointer instead. Using the original will lead to errors ( I've been there and done that...).

```void printgrid(std::vector<std::vector<std::shared_ptr<ChessPiece>>>& array)```
Accepts a chessboard grid as a parameter, and will visualize and print it to the terminal. That way you can see what happens to the pawn on the chessboard. Good for debugging.

```float calculateScaleFactor(const sf::Texture& texture, int squareSize)```
Finds out which size a texture (for example a pawn's image texture) should have, compared to the size of the square sizes on the chessboard.

```void initializePieces(std::vector<sf::Sprite>& sprites, int squareSize, std::vector<std::shared_ptr<ChessPiece>>& pieces)```
Handles setting the textures for each piece on the chessboard, along with position of the texture (visually) and the scaling.

```bool verifyPosition(std::vector<int> position)```
Check if a position is within the chessboard, meaning somewhere between [0, 0] and [8, 8]. If it's not, it'll return "false".

## ChessBoard
```std::shared_ptr<ChessPiece> getPosition(std::vector<int> position)```
Check the specific position on the chessboard [row, column], and find out what it contains. The function will return a pointer to either a chesspiece or a nullptr.

```void placePiece(std::shared_ptr<ChessPiece>& chessPiece, std::vector<int> position)```
Place a specific piece on a specific position on the chessboard. It can be used to move pieces, if you have the pointer to the chess piece. This function is quite similar to `ChessBoard.movePiece()`

```void movePiece(std::vector<int> fromPos, std::vector<int> toPos)```
Move whatever piece at "fromPos" to the new position "toPos". This does NOT check if there's already a pawn at the "toPos", so use carefully. The positions are in the format: [row, column].
The function is similar to `ChessBoard.placePiece()`.

```void wipePosition(std::vector<int> position)```
Take the given position on the chessboard and replace it with a nullptr. Any piece by that spot will be "forgotten" from the board. Use carefully.

```std::vector<std::shared_ptr<ChessPiece>> ChessBoard::getPieces()```
Returns an array with pointers to all chesspieces on the board.

```std::vector<std::vector<std::shared_ptr<ChessPiece>>> getGrid()```
Will return a nested array/vector containing the chessboard in the format: [rows[columns]]. The grid keeps track of all chess pieces related to it.

## ChessPiece
```void displayInfo() const```
Outputs a bit of information about the chess piece. Has no real use beyond debugging.

```std::string getType() const```
Returns the chess piece type of the object. For example "Pawn".

```std::vector<int> getPosition() const```
Returns the position on the chessboard of the piece, in the format: [row, column].

```void setPosition(std::vector<int> position)```
Sets the position of the chess piece. This only affects the piece itself.
It does not change the chessboard. You might want to use `ChessBoard.placePiece()` or `ChessBoard.movePiece()` instead.