create index _dta_index_store_sales_6_1333579789__k1_k23_k14_k6_k8_k5_k7_3_4_9_10_11_12_13_16_17_20 on store_sales
(
	ss_sold_date_sk asc,
	ss_net_profit asc,
	ss_sales_price asc,
	ss_hdemo_sk asc,
	ss_store_sk asc,
	ss_cdemo_sk asc,
	ss_addr_sk asc
)
include(ss_item_sk,ss_customer_sk,ss_promo_sk,ss_ticket_number,ss_quantity,ss_wholesale_cost,ss_list_price,ss_ext_sales_price,ss_ext_wholesale_cost,ss_coupon_amt) 
;
create index _dta_index_store_sales_6_1333579789__k1_k5_k8_k3_11_13_14_20 on store_sales
(
	ss_sold_date_sk asc,
	ss_cdemo_sk asc,
	ss_store_sk asc,
	ss_item_sk asc
)
include(ss_quantity,ss_list_price,ss_sales_price,ss_coupon_amt) 
;
create index _dta_index_store_sales_6_1333579789__k1_k3_k10_k4_k8_9_16_23 on store_sales
(
	ss_sold_date_sk asc,
	ss_item_sk asc,
	ss_ticket_number asc,
	ss_customer_sk asc,
	ss_store_sk asc
)
include(ss_promo_sk,ss_ext_sales_price,ss_net_profit) 
;
create index _dta_index_store_sales_6_1333579789__k4_1_3_10_11_14 on store_sales
(
	ss_customer_sk asc
)
include(ss_sold_date_sk,ss_item_sk,ss_ticket_number,ss_quantity,ss_sales_price) 
;
create index _dta_index_store_sales_6_1333579789__k1_k3_k10_k4_k8_23 on store_sales
(
	ss_sold_date_sk asc,
	ss_item_sk asc,
	ss_ticket_number asc,
	ss_customer_sk asc,
	ss_store_sk asc
)
include(ss_net_profit) 
;
create index _dta_index_store_sales_6_1333579789__k1_k8_3_14_16 on store_sales
(
	ss_sold_date_sk asc,
	ss_store_sk asc
)
include(ss_item_sk,ss_sales_price,ss_ext_sales_price) 
;
create index _dta_index_store_sales_6_1333579789__k3_k10_k4_k1_k8 on store_sales
(
	ss_item_sk asc,
	ss_ticket_number asc,
	ss_customer_sk asc,
	ss_sold_date_sk asc,
	ss_store_sk asc
)
;
create index _dta_index_store_sales_6_1333579789__k1_k3_k7_16 on store_sales
(
	ss_sold_date_sk asc,
	ss_item_sk asc,
	ss_addr_sk asc
)
include(ss_ext_sales_price) 
;
create index _dta_index_store_sales_6_1333579789__k1_k7_k3_16 on store_sales
(
	ss_sold_date_sk asc,
	ss_addr_sk asc,
	ss_item_sk asc
)
include(ss_ext_sales_price) 
;
create index _dta_index_store_sales_6_1333579789__k1_k3_11_13 on store_sales
(
	ss_sold_date_sk asc,
	ss_item_sk asc
)
include(ss_quantity,ss_list_price) 
;
create index _dta_index_store_sales_6_1333579789__k1_k4_k3_k10 on store_sales
(
	ss_sold_date_sk asc,
	ss_customer_sk asc,
	ss_item_sk asc,
	ss_ticket_number asc
)
;
create index _dta_index_store_sales_6_1333579789__k4_k1_16 on store_sales
(
	ss_customer_sk asc,
	ss_sold_date_sk asc
)
include(ss_ext_sales_price) 
;
create index _dta_index_store_sales_6_1333579789__k3_k10_k4 on store_sales
(
	ss_item_sk asc,
	ss_ticket_number asc,
	ss_customer_sk asc
)
;
create index _dta_index_store_sales_6_1333579789__k10_k3 on store_sales
(
	ss_ticket_number asc,
	ss_item_sk asc
)
;
create index _dta_index_catalog_sales_6_1301579675__k1_k16_k5_k4_3_6_18_19_21_22_28_34 on catalog_sales
(
	cs_sold_date_sk asc,
	cs_item_sk asc,
	cs_bill_cdemo_sk asc,
	cs_bill_customer_sk asc
)
include(cs_ship_date_sk,cs_bill_hdemo_sk,cs_order_number,cs_quantity,cs_list_price,cs_sales_price,cs_coupon_amt,cs_net_profit) 
;
create index _dta_index_catalog_sales_6_1301579675__k17_k6_k3_k5_k1_k16_12_14_15_18_19 on catalog_sales
(
	cs_promo_sk asc,
	cs_bill_hdemo_sk asc,
	cs_ship_date_sk asc,
	cs_bill_cdemo_sk asc,
	cs_sold_date_sk asc,
	cs_item_sk asc
)
include(cs_call_center_sk,cs_ship_mode_sk,cs_warehouse_sk,cs_order_number,cs_quantity) 
;
create index _dta_index_catalog_sales_6_1301579675__k1_4_16_18_19_21_24 on catalog_sales
(
	cs_sold_date_sk asc
)
include(cs_bill_customer_sk,cs_item_sk,cs_order_number,cs_quantity,cs_list_price,cs_ext_sales_price) 
;
create index _dta_index_catalog_sales_6_1301579675__k3_k12_k14_k15_16_18 on catalog_sales
(
	cs_ship_date_sk asc,
	cs_call_center_sk asc,
	cs_ship_mode_sk asc,
	cs_warehouse_sk asc
)
include(cs_item_sk,cs_order_number) 
;
create index _dta_index_catalog_sales_6_1301579675__k1_k16_k4_18_34 on catalog_sales
(
	cs_sold_date_sk asc,
	cs_item_sk asc,
	cs_bill_customer_sk asc
)
include(cs_order_number,cs_net_profit) 
;
create index _dta_index_catalog_sales_6_1301579675__k3_1_12_14_15 on catalog_sales
(
	cs_ship_date_sk asc
)
include(cs_sold_date_sk,cs_call_center_sk,cs_ship_mode_sk,cs_warehouse_sk) 
;
create index _dta_index_catalog_sales_6_1301579675__k16_k4_k1_34 on catalog_sales
(
	cs_item_sk asc,
	cs_bill_customer_sk asc,
	cs_sold_date_sk asc
)
include(cs_net_profit) 
;
create index _dta_index_catalog_sales_6_1301579675__k16_k18_26 on catalog_sales
(
	cs_item_sk asc,
	cs_order_number asc
)
include(cs_ext_list_price) 
;
create index _dta_index_catalog_sales_6_1301579675__k1_k4 on catalog_sales
(
	cs_sold_date_sk asc,
	cs_bill_customer_sk asc
)
;
create index _dta_index_catalog_sales_6_1301579675__k1_4 on catalog_sales
(
	cs_sold_date_sk asc
)
include(cs_bill_customer_sk) 
;
create index _dta_index_web_sales_6_1269579561__k3_k18_k12_k14_16_29_34 on web_sales
(
	ws_ship_date_sk asc,
	ws_order_number asc,
	ws_ship_addr_sk asc,
	ws_web_site_sk asc
)
include(ws_warehouse_sk,ws_ext_ship_cost,ws_net_profit) 
;
create index _dta_index_web_sales_6_1269579561__k1_k4_k5_18 on web_sales
(
	ws_sold_date_sk asc,
	ws_item_sk asc,
	ws_bill_customer_sk asc
)
include(ws_order_number) 
;
create index _dta_index_web_sales_6_1269579561__k1_8_24 on web_sales
(
	ws_sold_date_sk asc
)
include(ws_bill_addr_sk,ws_ext_sales_price) 
;
create index _dta_index_web_sales_6_1269579561__k18_16 on web_sales
(
	ws_order_number asc
)
include(ws_warehouse_sk) 
;
create index _dta_index_web_sales_6_1269579561__k1_k5 on web_sales
(
	ws_sold_date_sk asc,
	ws_bill_customer_sk asc
)
;
create index _dta_index_store_returns_6_1013578649__k1_3_4_10_20 on store_returns
(
	sr_returned_date_sk asc
)
include(sr_item_sk,sr_customer_sk,sr_ticket_number,sr_net_loss) 
;
create index _dta_index_store_returns_6_1013578649__k5_1_3_10_11 on store_returns
(
	sr_cdemo_sk asc
)
include(sr_returned_date_sk,sr_item_sk,sr_ticket_number,sr_return_quantity) 
;
create index _dta_index_store_returns_6_1013578649__k1_3_4_10 on store_returns
(
	sr_returned_date_sk asc
)
include(sr_item_sk,sr_customer_sk,sr_ticket_number) 
;


;
create index _dta_index_customer_6_949578421__k9_k10 on customer
(
	c_first_name asc,
	c_last_name asc
)
;
create index _dta_index_customer_6_949578421__k1_k5 on customer
(
	c_customer_sk asc,
	c_current_addr_sk asc
)
;
create index _dta_index_item_6_853578079__k1_2_5 on item
(
	i_item_sk asc
)
include(i_item_id,i_item_desc) 
;


;
create index _dta_index_item_6_853578079__k13_k11_k1 on item
(
	i_category asc,
	i_class asc,
	i_item_sk asc
)
;


;
create index _dta_index_item_6_853578079__k18 on item
(
	i_color asc
)
;


;
create index _dta_index_item_6_853578079__k2_k1 on item
(
	i_item_id asc,
	i_item_sk asc
)
;
create index _dta_index_date_dim_6_661577395__k7_k4_k9_k1 on date_dim
(
	d_year asc,
	d_month_seq asc,
	d_moy asc,
	d_date_sk asc
)
;
create index _dta_index_date_dim_6_661577395__k7_k9_k1 on date_dim
(
	d_year asc,
	d_moy asc,
	d_date_sk asc
)
;
create index _dta_index_date_dim_6_661577395__k1_k7_k9 on date_dim
(
	d_date_sk asc,
	d_year asc,
	d_moy asc
)
;
create index _dta_index_date_dim_6_661577395__k7_k11_k1 on date_dim
(
	d_year asc,
	d_qoy asc,
	d_date_sk asc
)
;
create index _dta_index_date_dim_6_661577395__k9_k7_k1 on date_dim
(
	d_moy asc,
	d_year asc,
	d_date_sk asc
)
;
create index _dta_index_date_dim_6_661577395__k4_1 on date_dim
(
	d_month_seq asc
)
include(d_date_sk) 
;
create index _dta_index_date_dim_6_661577395__k7_k1 on date_dim
(
	d_year asc,
	d_date_sk asc
)
;
create index _dta_index_date_dim_6_661577395__k7_k9 on date_dim
(
	d_year asc,
	d_moy asc
)
;
create index _dta_index_date_dim_6_661577395__k4_k3 on date_dim
(
	d_month_seq asc,
	d_date asc
)
;
create index _dta_index_store_6_885578193__k1_2_6 on store
(
	s_store_sk asc
)
include(s_store_id,s_store_name) 
;


;
create index _dta_index_store_6_885578193__k25_k1 on store
(
	s_state asc,
	s_store_sk asc
)
;
-- indexes created for q19

create index _dta_index_store_sales_5_1333579789__k4_k8_k3_k1_16 on store_sales
(
	ss_customer_sk asc,
	ss_store_sk asc,
	ss_item_sk asc,
	ss_sold_date_sk asc
)
include(ss_ext_sales_price) 
;
create index _dta_index_customer_5_949578421__k13_k5 on customer
(
	c_birth_month asc,
	c_current_addr_sk asc
)
;