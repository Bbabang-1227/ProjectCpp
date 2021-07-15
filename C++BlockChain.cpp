#include <ctime>
#include <vector>
#include <iostream>
#include <string>
using namespace std;

//Transaction DATA
struct TransactionData
{
	double amount;
	string senderKey;
	string receiverKey;
	time_t timestamp;
};

class Block
{
private:
	int index;
	size_t blockHash;
	size_t previousHash;
	size_t generateHash();
public:
	//Constructor
	Block(int idx, TransactionData d, size_t prevHash);

	//Get Original Hash
	size_t getHash();

	//Get Previous Hash
	size_t getPreviousHash();

	//Transaction Data
	TransactionData data;

	//Validate Hash
	bool isHashValid();
};

// Constructor witm params
Block::Block(int idx, TransactionData d, size_t prevHash)
{
	index = idx;
	data = d;
	previousHash = prevHash;
	blockHash = generateHash();
}

//private function
size_t Block::generateHash()
{
	hash<string> hash1;
	hash<size_t> hash2;
	hash<size_t> finalhash;
	string toHash = to_string(data.amount) + data.receiverKey + data.senderKey + to_string(data.timestamp);

	return finalhash(hash1(toHash) + hash2(previousHash));
}

size_t Block::getHash()
{
	return blockHash;
}

size_t Block::getPreviousHash()
{
	return previousHash;
}

bool Block::isHashValid()
{
	return generateHash() == blockHash;
}

//BlockChain-Class
class Blockchain
{
private:
	Block createGenesisBlock();
public:
	//Public Chain
	vector<Block> chain;

	//Constructor
	Blockchain();

	//Public Function
	void addBlock(TransactionData data);
	bool isChainValid();

	//Contrived Example For Demo Only!!!
	Block* getLatestBlock();
};

//Blockchain Constructor
Blockchain::Blockchain()
{
	Block genesis = createGenesisBlock();
	chain.push_back(genesis);
}

Block Blockchain::createGenesisBlock()
{
	time_t current;
	TransactionData d;
	d.amount = 0;
	d.receiverKey = "None";
	d.senderKey = "None";
	d.timestamp = time(&current);

	hash<int> hash1;
	Block genesis(0, d, hash1(0));
	return genesis;
}

//Bad only for demo
//�� �޸� �ּ� ������ �����͸� ������ �� �ִٴ� ��
//�����Ͱ� ������ ü�ο��� ���� �ֱ� ����� ��ȯ������ �̴� �����Ҽ� ������
//�޸� �ּҸ� ��ȯ�ϹǷ� �ش� �ּ� ������ �����͸� �����Ҽ� �����Ƿ� �����͸� ��ȯ
Block* Blockchain::getLatestBlock()
{
	return &chain.back();
}

void Blockchain::addBlock(TransactionData d)
{
	int index = (int)chain.size() - 1;
	Block newBlock(index, d, getLatestBlock()->getHash());
}

bool Blockchain::isChainValid()
{
	vector<Block>::iterator it;
	int chainLen = (int)chain.size();

	for (it = chain.begin(); it != chain.end(); it++)
	{
		Block currentBlock = *it;
		if (!currentBlock.isHashValid())
		{
			//INVALID!!
			return false;
		}

		if (chainLen > 1)
		{
			Block previousBlock = *(it - 1);
			if (currentBlock.getPreviousHash() != previousBlock.getHash())
			{
				return false;
			}
		}
	}
	return true;
}

int main()
{
	//START
	Blockchain AwesomeCoin;

	//Data for first added block
	TransactionData data1;
	time_t data1Time;
	data1.amount = 1.5;
	data1.receiverKey = "Joe";
	data1.senderKey = "Sally";
	data1.timestamp = time(&data1Time);

	AwesomeCoin.addBlock(data1);

	cout << "Is chain valid? " << endl
		<< AwesomeCoin.isChainValid() << endl;

	TransactionData data2;
	time_t data2Time;
	data2.amount = 0.00013322;
	data2.receiverKey = "Martha";
	data2.senderKey = "Fred";
	data2.timestamp = time(&data2Time);

	AwesomeCoin.addBlock(data2);
	cout << "Is chain valid? " << endl
		<< AwesomeCoin.isChainValid() << endl;

	//���ۺҰ���
	Block* hackBlock = AwesomeCoin.getLatestBlock();
	hackBlock->data.amount = 10000;
	hackBlock->data.receiverKey = "Jon";

	cout << "Now is the chail still vaild???" << endl;
	cout << AwesomeCoin.isChainValid() << endl;
}