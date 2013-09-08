/******************************************************************************
 *
<<<<<<< HEAD
 * Copyright(c) 2009-2012  Realtek Corporation.
=======
 * Copyright(c) 2009-2010  Realtek Corporation.
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
 *
 * The full GNU General Public License is included in this distribution in the
 * file called LICENSE.
 *
 * Contact Information:
 * wlanfae <wlanfae@realtek.com>
 * Realtek Corporation, No. 2, Innovation Road II, Hsinchu Science Park,
 * Hsinchu 300, Taiwan.
 *
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 *****************************************************************************/

#include "../wifi.h"
#include "../base.h"
#include "../pci.h"
#include "reg.h"
#include "def.h"
#include "phy.h"
#include "dm.h"
#include "../rtl8192c/fw_common.h"

void rtl92ce_dm_dynamic_txpower(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &(rtlpriv->phy);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	long undecorated_smoothed_pwdb;

	if (!rtlpriv->dm.dynamic_txpower_enable)
		return;

	if (rtlpriv->dm.dm_flag & HAL_DM_HIPWR_DISABLE) {
		rtlpriv->dm.dynamic_txhighpower_lvl = TXHIGHPWRLEVEL_NORMAL;
		return;
	}

	if ((mac->link_state < MAC80211_LINKED) &&
	    (rtlpriv->dm.entry_min_undecoratedsmoothed_pwdb == 0)) {
		RT_TRACE(rtlpriv, COMP_POWER, DBG_TRACE,
<<<<<<< HEAD
			 "Not connected to any\n");
=======
			 ("Not connected to any\n"));
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

		rtlpriv->dm.dynamic_txhighpower_lvl = TXHIGHPWRLEVEL_NORMAL;

		rtlpriv->dm.last_dtp_lvl = TXHIGHPWRLEVEL_NORMAL;
		return;
	}

	if (mac->link_state >= MAC80211_LINKED) {
		if (mac->opmode == NL80211_IFTYPE_ADHOC) {
			undecorated_smoothed_pwdb =
			    rtlpriv->dm.entry_min_undecoratedsmoothed_pwdb;
			RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD,
<<<<<<< HEAD
				 "AP Client PWDB = 0x%lx\n",
				 undecorated_smoothed_pwdb);
=======
				 ("AP Client PWDB = 0x%lx\n",
				  undecorated_smoothed_pwdb));
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		} else {
			undecorated_smoothed_pwdb =
			    rtlpriv->dm.undecorated_smoothed_pwdb;
			RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD,
<<<<<<< HEAD
				 "STA Default Port PWDB = 0x%lx\n",
				 undecorated_smoothed_pwdb);
=======
				 ("STA Default Port PWDB = 0x%lx\n",
				  undecorated_smoothed_pwdb));
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		}
	} else {
		undecorated_smoothed_pwdb =
		    rtlpriv->dm.entry_min_undecoratedsmoothed_pwdb;

		RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD,
<<<<<<< HEAD
			 "AP Ext Port PWDB = 0x%lx\n",
			 undecorated_smoothed_pwdb);
=======
			 ("AP Ext Port PWDB = 0x%lx\n",
			  undecorated_smoothed_pwdb));
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	}

	if (undecorated_smoothed_pwdb >= TX_POWER_NEAR_FIELD_THRESH_LVL2) {
		rtlpriv->dm.dynamic_txhighpower_lvl = TXHIGHPWRLEVEL_LEVEL1;
		RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD,
<<<<<<< HEAD
			 "TXHIGHPWRLEVEL_LEVEL1 (TxPwr=0x0)\n");
=======
			 ("TXHIGHPWRLEVEL_LEVEL1 (TxPwr=0x0)\n"));
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	} else if ((undecorated_smoothed_pwdb <
		    (TX_POWER_NEAR_FIELD_THRESH_LVL2 - 3)) &&
		   (undecorated_smoothed_pwdb >=
		    TX_POWER_NEAR_FIELD_THRESH_LVL1)) {

		rtlpriv->dm.dynamic_txhighpower_lvl = TXHIGHPWRLEVEL_LEVEL1;
		RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD,
<<<<<<< HEAD
			 "TXHIGHPWRLEVEL_LEVEL1 (TxPwr=0x10)\n");
=======
			 ("TXHIGHPWRLEVEL_LEVEL1 (TxPwr=0x10)\n"));
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	} else if (undecorated_smoothed_pwdb <
		   (TX_POWER_NEAR_FIELD_THRESH_LVL1 - 5)) {
		rtlpriv->dm.dynamic_txhighpower_lvl = TXHIGHPWRLEVEL_NORMAL;
		RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD,
<<<<<<< HEAD
			 "TXHIGHPWRLEVEL_NORMAL\n");
=======
			 ("TXHIGHPWRLEVEL_NORMAL\n"));
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	}

	if ((rtlpriv->dm.dynamic_txhighpower_lvl != rtlpriv->dm.last_dtp_lvl)) {
		RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD,
<<<<<<< HEAD
			 "PHY_SetTxPowerLevel8192S() Channel = %d\n",
			 rtlphy->current_channel);
=======
			 ("PHY_SetTxPowerLevel8192S() Channel = %d\n",
			  rtlphy->current_channel));
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		rtl92c_phy_set_txpower_level(hw, rtlphy->current_channel);
	}

	rtlpriv->dm.last_dtp_lvl = rtlpriv->dm.dynamic_txhighpower_lvl;
}
