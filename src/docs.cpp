#include <docs.hpp>

namespace hypha
{

   docs::docs(name self, name code, datastream<const char *> ds) : contract(self, code, ds) {}
   docs::~docs() {}

   void docs::create(name &creator, ContentGroups &content_groups)
   {
      require_auth( has_auth(creator) ? creator : get_self() );
      Document document(get_self(), creator, content_groups);

   }

   void docs::createhash(name &creator, ContentGroups &content_groups)
   {
      require_auth( has_auth(creator) ? creator : get_self() );
      // Document HashDocument(get_self(), creator, content_groups);

   }

   void docs::createdual (name &creator, ContentGroups &content_groups)
   {
      require_auth( has_auth(creator) ? creator : get_self() );
      Document Document(get_self(), creator, content_groups);
      HashDocument HashDocument(get_self(), creator, content_groups);
   }

   void docs::newhashdoc( eosio::name &creator )
   {
      require_auth( has_auth(creator) ? creator : get_self() );


   }

   void docs::makehashdoc( eosio::name &creator, const eosio::checksum256& _hash )
   {
      // require_auth( has_auth(creator) ? creator : get_self() );
      // bool document_exists = HashDocument.exists(_self, _hash);
      // check( document_exists, "no document" );

   }
} // namespace hypha