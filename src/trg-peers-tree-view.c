/*
 * transmission-remote-gtk - Transmission RPC client for GTK
 * Copyright (C) 2011  Alan Fitton

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef HAVE_GEOIP
#include <GeoIP.h>
#endif

#include <glib-object.h>
#include <glib/gi18n.h>
#include <gtk/gtk.h>

#include "trg-tree-view.h"
#include "trg-peers-model.h"
#include "trg-peers-tree-view.h"

G_DEFINE_TYPE(TrgPeersTreeView, trg_peers_tree_view, TRG_TYPE_TREE_VIEW)

static void
trg_peers_tree_view_class_init(TrgPeersTreeViewClass * klass G_GNUC_UNUSED)
{
}

static void trg_peers_tree_view_init(TrgPeersTreeView * self)
{
    TrgTreeView *ttv = TRG_TREE_VIEW(self);
    trg_column_description *desc;

    desc =
        trg_tree_view_reg_column(ttv, TRG_COLTYPE_ICONTEXT, PEERSCOL_ICON,
                                 _("IP"), "ip", 1);
    desc->model_column_icon = PEERSCOL_ICON;

    trg_tree_view_reg_column(ttv, TRG_COLTYPE_TEXT, PEERSCOL_HOST,
                             _("Host"), "host", 1);

#ifdef HAVE_GEOIP
    trg_tree_view_reg_column(ttv, TRG_COLTYPE_TEXT, PEERSCOL_COUNTRY,
                             _("Country"), "country", 1);
#endif
    trg_tree_view_reg_column(ttv, TRG_COLTYPE_SPEED, PEERSCOL_DOWNSPEED,
                             _("Down Speed"), "down-speed", 1);
    trg_tree_view_reg_column(ttv, TRG_COLTYPE_SPEED, PEERSCOL_UPSPEED,
                             _("Up Speed"), "up-speed", 1);
    trg_tree_view_reg_column(ttv, TRG_COLTYPE_PROG, PEERSCOL_PROGRESS,
                             _("Progress"), "progress", 1);
    trg_tree_view_reg_column(ttv, TRG_COLTYPE_TEXT, PEERSCOL_FLAGS,
                             _("Flags"), "flags", 1);
    trg_tree_view_reg_column(ttv, TRG_COLTYPE_TEXT, PEERSCOL_CLIENT,
                             _("Client"), "client", 1);

    gtk_tree_view_set_search_column(GTK_TREE_VIEW(self), PEERSCOL_HOST);
    trg_tree_view_setup_columns(ttv);
}

TrgPeersTreeView *trg_peers_tree_view_new(TrgPeersModel * model)
{
    GObject *obj = g_object_new(TRG_TYPE_PEERS_TREE_VIEW, NULL);

    gtk_tree_view_set_model(GTK_TREE_VIEW(obj), GTK_TREE_MODEL(model));

    return TRG_PEERS_TREE_VIEW(obj);
}
