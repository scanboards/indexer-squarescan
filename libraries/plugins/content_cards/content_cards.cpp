/**
 * The Revolution Populi Project
 * Copyright (C) 2022 Revolution Populi Limited
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <graphene/content_cards/content_cards.hpp>

namespace graphene { namespace content_cards {

namespace detail
{

class content_cards_impl
{
   public:
      content_cards_impl(content_cards& _plugin)
         : _self( _plugin )
      {  }
      virtual ~content_cards_impl();

      void onBlock( const signed_block& b );

      graphene::chain::database& database()
      {
         return _self.database();
      }

      content_cards& _self;

      std::string _plugin_option = "";

   private:

};

void content_cards_impl::onBlock( const signed_block& b )
{
   wdump((b.block_num()));
}

content_cards_impl::~content_cards_impl()
{
   return;
}

} // end namespace detail

content_cards::content_cards() :
   my( new detail::content_cards_impl(*this) )
{
}

content_cards::~content_cards()
{
}

std::string content_cards::plugin_name()const
{
   return "content_cards";
}
std::string content_cards::plugin_description()const
{
   return "Stores full content of content_cards and allows access to them.";
}

void content_cards::plugin_set_program_options(
   boost::program_options::options_description& cli,
   boost::program_options::options_description& cfg
   )
{
   cli.add_options()
         ("content_cards_option", boost::program_options::value<std::string>(), "content_cards option")
         ;
   cfg.add(cli);
}

void content_cards::plugin_initialize(const boost::program_options::variables_map& options)
{
   database().applied_block.connect( [&]( const signed_block& b) {
      my->onBlock(b);
   } );

   if (options.count("content_cards")) {
      my->_plugin_option = options["content_cards"].as<std::string>();
   }
}

void content_cards::plugin_startup()
{
   ilog("content_cards: plugin_startup() begin");
}

} }
