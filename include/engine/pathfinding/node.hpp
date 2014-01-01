#ifndef QRW_NODE_HPP
#define QRW_NODE_HPP

#include "engine/coordinates.hpp"

namespace qrw
{
	class Node : public Coordinates
	{
		public:
			Node(int x, int y);
			Node(const Coordinates& coordinates);

			void setParent(Node* parent);
			Node* getParent();

			void setG(int g);
			int getG();

			void setH(int h);

			int getF();

		private:
			Node* parent;

			int g;
			int h;
	};
}

#endif
