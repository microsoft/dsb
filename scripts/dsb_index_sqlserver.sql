CREATE NONCLUSTERED INDEX [_dta_index_store_sales_6_1333579789__K1_K23_K14_K6_K8_K5_K7_3_4_9_10_11_12_13_16_17_20] ON [dbo].[store_sales]
(
	[ss_sold_date_sk] ASC,
	[ss_net_profit] ASC,
	[ss_sales_price] ASC,
	[ss_hdemo_sk] ASC,
	[ss_store_sk] ASC,
	[ss_cdemo_sk] ASC,
	[ss_addr_sk] ASC
)
INCLUDE([ss_item_sk],[ss_customer_sk],[ss_promo_sk],[ss_ticket_number],[ss_quantity],[ss_wholesale_cost],[ss_list_price],[ss_ext_sales_price],[ss_ext_wholesale_cost],[ss_coupon_amt]) WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;

CREATE NONCLUSTERED INDEX [_dta_index_store_sales_6_1333579789__K1_K5_K8_K3_11_13_14_20] ON [dbo].[store_sales]
(
	[ss_sold_date_sk] ASC,
	[ss_cdemo_sk] ASC,
	[ss_store_sk] ASC,
	[ss_item_sk] ASC
)
INCLUDE([ss_quantity],[ss_list_price],[ss_sales_price],[ss_coupon_amt]) WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;

CREATE NONCLUSTERED INDEX [_dta_index_store_sales_6_1333579789__K1_K3_K10_K4_K8_9_16_23] ON [dbo].[store_sales]
(
	[ss_sold_date_sk] ASC,
	[ss_item_sk] ASC,
	[ss_ticket_number] ASC,
	[ss_customer_sk] ASC,
	[ss_store_sk] ASC
)
INCLUDE([ss_promo_sk],[ss_ext_sales_price],[ss_net_profit]) WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;

CREATE NONCLUSTERED INDEX [_dta_index_store_sales_6_1333579789__K4_1_3_10_11_14] ON [dbo].[store_sales]
(
	[ss_customer_sk] ASC
)
INCLUDE([ss_sold_date_sk],[ss_item_sk],[ss_ticket_number],[ss_quantity],[ss_sales_price]) WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;

CREATE NONCLUSTERED INDEX [_dta_index_store_sales_6_1333579789__K1_K3_K10_K4_K8_23] ON [dbo].[store_sales]
(
	[ss_sold_date_sk] ASC,
	[ss_item_sk] ASC,
	[ss_ticket_number] ASC,
	[ss_customer_sk] ASC,
	[ss_store_sk] ASC
)
INCLUDE([ss_net_profit]) WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;

CREATE NONCLUSTERED INDEX [_dta_index_store_sales_6_1333579789__K1_K8_3_14_16] ON [dbo].[store_sales]
(
	[ss_sold_date_sk] ASC,
	[ss_store_sk] ASC
)
INCLUDE([ss_item_sk],[ss_sales_price],[ss_ext_sales_price]) WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;

CREATE NONCLUSTERED INDEX [_dta_index_store_sales_6_1333579789__K3_K10_K4_K1_K8] ON [dbo].[store_sales]
(
	[ss_item_sk] ASC,
	[ss_ticket_number] ASC,
	[ss_customer_sk] ASC,
	[ss_sold_date_sk] ASC,
	[ss_store_sk] ASC
)WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;

CREATE NONCLUSTERED INDEX [_dta_index_store_sales_6_1333579789__K1_K3_K7_16] ON [dbo].[store_sales]
(
	[ss_sold_date_sk] ASC,
	[ss_item_sk] ASC,
	[ss_addr_sk] ASC
)
INCLUDE([ss_ext_sales_price]) WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;

CREATE NONCLUSTERED INDEX [_dta_index_store_sales_6_1333579789__K1_K7_K3_16] ON [dbo].[store_sales]
(
	[ss_sold_date_sk] ASC,
	[ss_addr_sk] ASC,
	[ss_item_sk] ASC
)
INCLUDE([ss_ext_sales_price]) WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;

CREATE NONCLUSTERED INDEX [_dta_index_store_sales_6_1333579789__K1_K3_11_13] ON [dbo].[store_sales]
(
	[ss_sold_date_sk] ASC,
	[ss_item_sk] ASC
)
INCLUDE([ss_quantity],[ss_list_price]) WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;

CREATE NONCLUSTERED INDEX [_dta_index_store_sales_6_1333579789__K1_K4_K3_K10] ON [dbo].[store_sales]
(
	[ss_sold_date_sk] ASC,
	[ss_customer_sk] ASC,
	[ss_item_sk] ASC,
	[ss_ticket_number] ASC
)WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;

CREATE NONCLUSTERED INDEX [_dta_index_store_sales_6_1333579789__K4_K1_16] ON [dbo].[store_sales]
(
	[ss_customer_sk] ASC,
	[ss_sold_date_sk] ASC
)
INCLUDE([ss_ext_sales_price]) WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;

CREATE NONCLUSTERED INDEX [_dta_index_store_sales_6_1333579789__K3_K10_K4] ON [dbo].[store_sales]
(
	[ss_item_sk] ASC,
	[ss_ticket_number] ASC,
	[ss_customer_sk] ASC
)WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;

CREATE NONCLUSTERED INDEX [_dta_index_store_sales_6_1333579789__K10_K3] ON [dbo].[store_sales]
(
	[ss_ticket_number] ASC,
	[ss_item_sk] ASC
)WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;

CREATE NONCLUSTERED INDEX [_dta_index_catalog_sales_6_1301579675__K1_K16_K5_K4_3_6_18_19_21_22_28_34] ON [dbo].[catalog_sales]
(
	[cs_sold_date_sk] ASC,
	[cs_item_sk] ASC,
	[cs_bill_cdemo_sk] ASC,
	[cs_bill_customer_sk] ASC
)
INCLUDE([cs_ship_date_sk],[cs_bill_hdemo_sk],[cs_order_number],[cs_quantity],[cs_list_price],[cs_sales_price],[cs_coupon_amt],[cs_net_profit]) WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;

CREATE NONCLUSTERED INDEX [_dta_index_catalog_sales_6_1301579675__K17_K6_K3_K5_K1_K16_12_14_15_18_19] ON [dbo].[catalog_sales]
(
	[cs_promo_sk] ASC,
	[cs_bill_hdemo_sk] ASC,
	[cs_ship_date_sk] ASC,
	[cs_bill_cdemo_sk] ASC,
	[cs_sold_date_sk] ASC,
	[cs_item_sk] ASC
)
INCLUDE([cs_call_center_sk],[cs_ship_mode_sk],[cs_warehouse_sk],[cs_order_number],[cs_quantity]) WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;

CREATE NONCLUSTERED INDEX [_dta_index_catalog_sales_6_1301579675__K1_4_16_18_19_21_24] ON [dbo].[catalog_sales]
(
	[cs_sold_date_sk] ASC
)
INCLUDE([cs_bill_customer_sk],[cs_item_sk],[cs_order_number],[cs_quantity],[cs_list_price],[cs_ext_sales_price]) WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;

CREATE NONCLUSTERED INDEX [_dta_index_catalog_sales_6_1301579675__K3_K12_K14_K15_16_18] ON [dbo].[catalog_sales]
(
	[cs_ship_date_sk] ASC,
	[cs_call_center_sk] ASC,
	[cs_ship_mode_sk] ASC,
	[cs_warehouse_sk] ASC
)
INCLUDE([cs_item_sk],[cs_order_number]) WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;

CREATE NONCLUSTERED INDEX [_dta_index_catalog_sales_6_1301579675__K1_K16_K4_18_34] ON [dbo].[catalog_sales]
(
	[cs_sold_date_sk] ASC,
	[cs_item_sk] ASC,
	[cs_bill_customer_sk] ASC
)
INCLUDE([cs_order_number],[cs_net_profit]) WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;

CREATE NONCLUSTERED INDEX [_dta_index_catalog_sales_6_1301579675__K3_1_12_14_15] ON [dbo].[catalog_sales]
(
	[cs_ship_date_sk] ASC
)
INCLUDE([cs_sold_date_sk],[cs_call_center_sk],[cs_ship_mode_sk],[cs_warehouse_sk]) WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;

CREATE NONCLUSTERED INDEX [_dta_index_catalog_sales_6_1301579675__K16_K4_K1_34] ON [dbo].[catalog_sales]
(
	[cs_item_sk] ASC,
	[cs_bill_customer_sk] ASC,
	[cs_sold_date_sk] ASC
)
INCLUDE([cs_net_profit]) WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;

CREATE NONCLUSTERED INDEX [_dta_index_catalog_sales_6_1301579675__K16_K18_26] ON [dbo].[catalog_sales]
(
	[cs_item_sk] ASC,
	[cs_order_number] ASC
)
INCLUDE([cs_ext_list_price]) WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;

CREATE NONCLUSTERED INDEX [_dta_index_catalog_sales_6_1301579675__K1_K4] ON [dbo].[catalog_sales]
(
	[cs_sold_date_sk] ASC,
	[cs_bill_customer_sk] ASC
)WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;

CREATE NONCLUSTERED INDEX [_dta_index_catalog_sales_6_1301579675__K1_4] ON [dbo].[catalog_sales]
(
	[cs_sold_date_sk] ASC
)
INCLUDE([cs_bill_customer_sk]) WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;

CREATE NONCLUSTERED INDEX [_dta_index_web_sales_6_1269579561__K3_K18_K12_K14_16_29_34] ON [dbo].[web_sales]
(
	[ws_ship_date_sk] ASC,
	[ws_order_number] ASC,
	[ws_ship_addr_sk] ASC,
	[ws_web_site_sk] ASC
)
INCLUDE([ws_warehouse_sk],[ws_ext_ship_cost],[ws_net_profit]) WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;

CREATE NONCLUSTERED INDEX [_dta_index_web_sales_6_1269579561__K1_K4_K5_18] ON [dbo].[web_sales]
(
	[ws_sold_date_sk] ASC,
	[ws_item_sk] ASC,
	[ws_bill_customer_sk] ASC
)
INCLUDE([ws_order_number]) WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;

CREATE NONCLUSTERED INDEX [_dta_index_web_sales_6_1269579561__K1_8_24] ON [dbo].[web_sales]
(
	[ws_sold_date_sk] ASC
)
INCLUDE([ws_bill_addr_sk],[ws_ext_sales_price]) WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;

CREATE NONCLUSTERED INDEX [_dta_index_web_sales_6_1269579561__K18_16] ON [dbo].[web_sales]
(
	[ws_order_number] ASC
)
INCLUDE([ws_warehouse_sk]) WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;

CREATE NONCLUSTERED INDEX [_dta_index_web_sales_6_1269579561__K1_K5] ON [dbo].[web_sales]
(
	[ws_sold_date_sk] ASC,
	[ws_bill_customer_sk] ASC
)WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;

CREATE NONCLUSTERED INDEX [_dta_index_store_returns_6_1013578649__K1_3_4_10_20] ON [dbo].[store_returns]
(
	[sr_returned_date_sk] ASC
)
INCLUDE([sr_item_sk],[sr_customer_sk],[sr_ticket_number],[sr_net_loss]) WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;

CREATE NONCLUSTERED INDEX [_dta_index_store_returns_6_1013578649__K5_1_3_10_11] ON [dbo].[store_returns]
(
	[sr_cdemo_sk] ASC
)
INCLUDE([sr_returned_date_sk],[sr_item_sk],[sr_ticket_number],[sr_return_quantity]) WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;

CREATE NONCLUSTERED INDEX [_dta_index_store_returns_6_1013578649__K1_3_4_10] ON [dbo].[store_returns]
(
	[sr_returned_date_sk] ASC
)
INCLUDE([sr_item_sk],[sr_customer_sk],[sr_ticket_number]) WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;

SET ANSI_PADDING ON

;

CREATE NONCLUSTERED INDEX [_dta_index_customer_6_949578421__K9_K10] ON [dbo].[customer]
(
	[c_first_name] ASC,
	[c_last_name] ASC
)WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;

CREATE NONCLUSTERED INDEX [_dta_index_customer_6_949578421__K1_K5] ON [dbo].[customer]
(
	[c_customer_sk] ASC,
	[c_current_addr_sk] ASC
)WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;

CREATE NONCLUSTERED INDEX [_dta_index_item_6_853578079__K1_2_5] ON [dbo].[item]
(
	[i_item_sk] ASC
)
INCLUDE([i_item_id],[i_item_desc]) WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;

SET ANSI_PADDING ON

;

CREATE NONCLUSTERED INDEX [_dta_index_item_6_853578079__K13_K11_K1] ON [dbo].[item]
(
	[i_category] ASC,
	[i_class] ASC,
	[i_item_sk] ASC
)WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;

SET ANSI_PADDING ON

;

CREATE NONCLUSTERED INDEX [_dta_index_item_6_853578079__K18] ON [dbo].[item]
(
	[i_color] ASC
)WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;

SET ANSI_PADDING ON

;

CREATE NONCLUSTERED INDEX [_dta_index_item_6_853578079__K2_K1] ON [dbo].[item]
(
	[i_item_id] ASC,
	[i_item_sk] ASC
)WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;

CREATE NONCLUSTERED INDEX [_dta_index_date_dim_6_661577395__K7_K4_K9_K1] ON [dbo].[date_dim]
(
	[d_year] ASC,
	[d_month_seq] ASC,
	[d_moy] ASC,
	[d_date_sk] ASC
)WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;

CREATE NONCLUSTERED INDEX [_dta_index_date_dim_6_661577395__K7_K9_K1] ON [dbo].[date_dim]
(
	[d_year] ASC,
	[d_moy] ASC,
	[d_date_sk] ASC
)WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;

CREATE NONCLUSTERED INDEX [_dta_index_date_dim_6_661577395__K1_K7_K9] ON [dbo].[date_dim]
(
	[d_date_sk] ASC,
	[d_year] ASC,
	[d_moy] ASC
)WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;

CREATE NONCLUSTERED INDEX [_dta_index_date_dim_6_661577395__K7_K11_K1] ON [dbo].[date_dim]
(
	[d_year] ASC,
	[d_qoy] ASC,
	[d_date_sk] ASC
)WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;

CREATE NONCLUSTERED INDEX [_dta_index_date_dim_6_661577395__K9_K7_K1] ON [dbo].[date_dim]
(
	[d_moy] ASC,
	[d_year] ASC,
	[d_date_sk] ASC
)WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;

CREATE NONCLUSTERED INDEX [_dta_index_date_dim_6_661577395__K4_1] ON [dbo].[date_dim]
(
	[d_month_seq] ASC
)
INCLUDE([d_date_sk]) WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;

CREATE NONCLUSTERED INDEX [_dta_index_date_dim_6_661577395__K7_K1] ON [dbo].[date_dim]
(
	[d_year] ASC,
	[d_date_sk] ASC
)WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;

CREATE NONCLUSTERED INDEX [_dta_index_date_dim_6_661577395__K7_K9] ON [dbo].[date_dim]
(
	[d_year] ASC,
	[d_moy] ASC
)WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;

CREATE NONCLUSTERED INDEX [_dta_index_date_dim_6_661577395__K4_K3] ON [dbo].[date_dim]
(
	[d_month_seq] ASC,
	[d_date] ASC
)WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;

CREATE NONCLUSTERED INDEX [_dta_index_store_6_885578193__K1_2_6] ON [dbo].[store]
(
	[s_store_sk] ASC
)
INCLUDE([s_store_id],[s_store_name]) WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;

SET ANSI_PADDING ON

;

CREATE NONCLUSTERED INDEX [_dta_index_store_6_885578193__K25_K1] ON [dbo].[store]
(
	[s_state] ASC,
	[s_store_sk] ASC
)WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;

-- indexes created for Q19

CREATE NONCLUSTERED INDEX [_dta_index_store_sales_5_1333579789__K4_K8_K3_K1_16] ON [dbo].[store_sales]
(
	[ss_customer_sk] ASC,
	[ss_store_sk] ASC,
	[ss_item_sk] ASC,
	[ss_sold_date_sk] ASC
)
INCLUDE([ss_ext_sales_price]) WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;

CREATE NONCLUSTERED INDEX [_dta_index_customer_5_949578421__K13_K5] ON [dbo].[customer]
(
	[c_birth_month] ASC,
	[c_current_addr_sk] ASC
)WITH (SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF) ON [PRIMARY]
;
