#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <iomanip>
class CHESS {

private:
	static const int MAX_size = 15;
	static const int MAX_win = 5;
	std::vector<std::vector<char>> board;
	std::vector<std::string >players;
	std::vector<char>symbols;
	int currentplayer;
	bool gameover;
	std::string winner;






public:
	CHESS() : board(MAX_size, std::vector<char>(MAX_size, '.')), currentplayer(0), gameover(false) {
		setupplayers();
	}
	void setupplayers() {
		int numsplayers;
		std::cout << "多人五子棋游戏";
		std::cout << "请输入玩家数量";
		while (true) {
			std::cin >> numsplayers;
			if (numsplayers <= 4 && numsplayers >= 2) {
				break;
			}
			std::cout << "请输入2-4";
		}
		std::cin.ignore();
		// 设置玩家符号
		std::vector<char> availableSymbols = { 'X', 'O', '#', '@' };

		for (int i = 0; i < numsplayers; i++) {
			std::string name;
			std::cout << "请输入玩家" << (i + 1) << "的名字";
			std::getline(std::cin, name);
			if (name.empty()) {
				name = "玩家" + std::to_string(i + 1);
			}
			players.push_back(name);
			symbols.push_back(availableSymbols[i]); // 修复越界问题
		}
		std::cout << "玩家设置完成";
		for (size_t i = 0; i < players.size(); i++) {
			std::cout << players[i] << " 使用符号: " << symbols[i] << "\n";

		}
		std::cout << "\n";
	}
	void printBoard() {
		std::cout << "\n   ";
		for (int i = 0; i < MAX_size; i++) {
			std::cout << std::setw(2) << i << " ";
		}
		std::cout << "\n";

		for (int i = 0; i < MAX_size; i++) {
			std::cout << std::setw(2) << i << " ";
			for (int j = 0; j < MAX_size; j++) {
				std::cout << " " << board[i][j] << " ";
			}
			std::cout << "\n";
		}
		std::cout << "\n";
	}
	bool isValidMove(int row, int col) {
		return row >= 0 && row < MAX_size &&
			col >= 0 && col < MAX_size &&
			board[row][col] == '.';
	}
	void makeMove(int row, int col) {
		board[row][col] = symbols[currentplayer];
	}
	bool checkWin(int row, int col) {
		char symbol = symbols[currentplayer];

		// 检查四个方向：水平、垂直、两个对角线
		int directions[4][2] = { {0, 1}, {1, 0}, {1, 1}, {1, -1} };

		for (int d = 0; d < 4; d++) {
			int count = 1; // 当前棋子
			int dr = directions[d][0];
			int dc = directions[d][1];

			// 向一个方向检查
			int r = row + dr, c = col + dc;
			while (r >= 0 && r < MAX_size && c >= 0 && c < MAX_size &&
				board[r][c] == symbol) {
				count++;
				r += dr;
				c += dc;
			}

			// 向相反方向检查
			r = row - dr;
			c = col - dc;
			while (r >= 0 && r <MAX_size && c >= 0 && c < MAX_size &&
				board[r][c] == symbol) {
				count++;
				r -= dr;
				c -= dc;
			}

			if (count >= MAX_win) {
				return true;
			}
		}
		return false;
	}
	bool isBoardFull() {
		for (int i = 0; i < MAX_size; i++) {
			for (int j = 0; j < MAX_size; j++) {
				if (board[i][j] == '.') {
					return false;
				}
			}
		}
		return true;
	}
	void nextPlayer() {
		currentplayer = (currentplayer + 1) % players.size();
	}
	void playGame() {
		std::cout << "游戏开始！目标：连成5子获胜\n";
		std::cout << "输入格式：行号 列号 (例如: 7 7)\n";
		std::cout << "输入 -1 -1 退出游戏\n\n";

		while (!gameover) {
			printBoard();

			std::cout << "轮到 " << players[currentplayer]
				<< " (" << symbols[currentplayer] << ") 下棋\n";
			std::cout << "请输入位置 (行 列): ";

			int row, col;
			if (!(std::cin >> row >> col)) {
				std::cout << "输入无效！请输入数字。\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				continue;
			}

			// 退出游戏
			if (row == -1 && col == -1) {
				std::cout << "游戏结束！\n";
				return;
			}

			if (!isValidMove(row, col)) {
				std::cout << "无效的位置！请选择空的位置。\n";
				continue;
			}

			makeMove(row, col);

			if (checkWin(row, col)) {
				winner = players[currentplayer];
				gameover = true;
				printBoard();
				std::cout << "🎉 恭喜！" << winner << " 获胜！🎉\n";
				break;
			}

			if (isBoardFull()) {
				gameover = true;
				printBoard();
				std::cout << "平局！棋盘已满。\n";
				break;
			}

			nextPlayer();
		}
	}

	void showGameStats() {
		if (!winner.empty()) {
			std::cout << "\n=== 游戏统计 ===\n";
			std::cout << "获胜者: " << winner << "\n";
			std::cout << "参与玩家: ";
			for (size_t i = 0; i < players.size(); i++) {
				std::cout << players[i];
				if (i < players.size() - 1) std::cout << ", ";
			}
			std::cout << "\n";
		}
	}

};

int main() {
	char playAgain;

	do {
		CHESS game;
		game.playGame();
		game.showGameStats();

		std::cout << "\n想再来一局吗？(y/n): ";
		std::cin >> playAgain;
		std::cout << "\n" << std::string(50, '=') << "\n";

	} while (playAgain == 'y' || playAgain == 'Y');

	std::cout << "感谢游戏！再见！\n";
	return 0;
}
