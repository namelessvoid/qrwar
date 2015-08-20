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

			void setParent(Node* _parent);
			Node* getParent();

			void setG(int g);
			int getG();

			void setH(int h);

			int getF();

		private:
			Node* _parent;

			int _g;
			int _h;
	};
}

#endif
