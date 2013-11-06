#ifndef RecipeSpelunkerServerHeaderPlusPlus
#define RecipeSpelunkerServerHeaderPlusPlus

#include <lacewing.h>

namespace rs
{
	namespace server
	{
		struct Server
		{
		private:
			struct Client;

			static void tick_forward(void *tag)
			{
				Server *s = static_cast<Server *>(tag);
				s->Tick();
				s->ep->post(&tick_forward, tag);
			}

		public:
			Server()
			{
				ep->post(&tick_forward, this);

				s->tag(this);
				s->on_error([](lacewing::server s, lacewing::error e) -> void
					{
						static_cast<Server *>(s->tag())->Error(e);
					});
				s->on_connect([](lacewing::server s, lacewing::server_client c) -> void
					{
						static_cast<Server *>(s->tag())->Connect(*new Client(c)); //Client ctor sets c->tag()
					});
				s->on_connect([](lacewing::server s, lacewing::server_client c, char const *data, std::size_t size) -> void
					{
						static_cast<Server *>(s->tag())->Data(*static_cast<Client *>(c->tag()), data, size);
					});
				s->on_disconnect([](lacewing::server s, lacewing::server_client c) -> void
					{
						Client *p = static_cast<Client *>(c->tag());
						static_cast<Server *>(s->tag())->Disconnect(*p);
						delete p;
					});

				s->host(25564);
			}
			~Server()
			{
				lacewing::server_delete(s), s = nullptr;
			}

			void Start()
			{
				lacewing::error e = ep->start_eventloop();
				//e->tostring()
				if(e) lacewing::error_delete(e), e = nullptr;
			}

			void Tick()
			{
			}

		private:
			lacewing::eventpump ep = lacewing::eventpump_new();
			lacewing::server s = lacewing::server_new(ep);

			void Connect(Client &c)
			{
			}
			void Disconnect(Client &c)
			{
			}

			void Data(Client &c, char const *data, std::size_t size)
			{
			}

			void Error(lacewing::error e)
			{
			}

			struct Client
			{
				Client(lacewing::server_client c)
				: c(c)
				{
					c->tag(this);
				}

			private:
				lacewing::server_client c;
			};
		};
	}
}

#endif
