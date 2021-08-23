--
-- Legal Notice
--
-- This document and associated source code (the "Work") is a part of a
-- benchmark specification maintained by the TPC.
--
-- The TPC reserves all right, title, and interest to the Work as provided
-- under U.S. and international laws, including without limitation all patent
-- and trademark rights therein.
--
-- No Warranty
--
-- 1.1 TO THE MAXIMUM EXTENT PERMITTED BY APPLICABLE LAW, THE INFORMATION
--     CONTAINED HEREIN IS PROVIDED "AS IS" AND WITH ALL FAULTS, AND THE
--     AUTHORS AND DEVELOPERS OF THE WORK HEREBY DISCLAIM ALL OTHER
--     WARRANTIES AND CONDITIONS, EITHER EXPRESS, IMPLIED OR STATUTORY,
--     INCLUDING, BUT NOT LIMITED TO, ANY (IF ANY) IMPLIED WARRANTIES,
--     DUTIES OR CONDITIONS OF MERCHANTABILITY, OF FITNESS FOR A PARTICULAR
--     PURPOSE, OF ACCURACY OR COMPLETENESS OF RESPONSES, OF RESULTS, OF
--     WORKMANLIKE EFFORT, OF LACK OF VIRUSES, AND OF LACK OF NEGLIGENCE.
--     ALSO, THERE IS NO WARRANTY OR CONDITION OF TITLE, QUIET ENJOYMENT,
--     QUIET POSSESSION, CORRESPONDENCE TO DESCRIPTION OR NON-INFRINGEMENT
--     WITH REGARD TO THE WORK.
-- 1.2 IN NO EVENT WILL ANY AUTHOR OR DEVELOPER OF THE WORK BE LIABLE TO
--     ANY OTHER PARTY FOR ANY DAMAGES, INCLUDING BUT NOT LIMITED TO THE
--     COST OF PROCURING SUBSTITUTE GOODS OR SERVICES, LOST PROFITS, LOSS
--     OF USE, LOSS OF DATA, OR ANY INCIDENTAL, CONSEQUENTIAL, DIRECT,
--     INDIRECT, OR SPECIAL DAMAGES WHETHER UNDER CONTRACT, TORT, WARRANTY,
--     OR OTHERWISE, ARISING IN ANY WAY OUT OF THIS OR ANY OTHER AGREEMENT
--     RELATING TO THE WORK, WHETHER OR NOT SUCH AUTHOR OR DEVELOPER HAD
--     ADVANCE NOTICE OF THE POSSIBILITY OF SUCH DAMAGES.
--
-- Contributors:
--
 define YEAR = random(1998, 2002, uniform);
 define SALES_DATE=date([YEAR]+"-01-01",[YEAR]+"-07-24",sales);
 define PRICE = range(random(1, 300, uniform), 10);
 define MANAGER=range(random(1, 100,uniform), 30);
 define BIRTH_YEAR = range(random (1925, 1993, uniform), 10);

 define _LIMIT=100;

 with ss_items as
 (select i_item_id item_id
       ,c_birth_year birth_year
        ,sum(ss_ext_sales_price) ss_item_rev
 from store_sales
     ,item
     ,date_dim
     ,customer
 where ss_item_sk = i_item_sk
   and d_date in (select d_date
                  from date_dim
                  where d_month_seq = (select d_month_seq
                                      from date_dim
                                      where d_date = '[SALES_DATE]'))
   and ss_sold_date_sk   = d_date_sk
   and ss_list_price between [PRICE.begin] and [PRICE.end]
   and i_manager_id BETWEEN [MANAGER.begin] and [MANAGER.end]
   and ss_customer_sk = c_customer_sk
   and c_birth_year BETWEEN [BIRTH_YEAR.begin] AND [BIRTH_YEAR.end]
group by i_item_id, c_birth_year),
 cs_items as
 (select i_item_id item_id
        ,c_birth_year birth_year
        ,sum(cs_ext_sales_price) cs_item_rev
  from catalog_sales
      ,item
      ,date_dim
      ,customer
 where cs_item_sk = i_item_sk
  and  d_date in (select d_date
                  from date_dim
                  where d_month_seq = (select d_month_seq
                                      from date_dim
                                      where d_date = '[SALES_DATE]'))
  and  cs_sold_date_sk = d_date_sk
  and  cs_list_price between [PRICE.begin] and [PRICE.end]
  and i_manager_id BETWEEN [MANAGER.begin] and [MANAGER.end]
  and cs_bill_customer_sk = c_customer_sk
  and c_birth_year BETWEEN [BIRTH_YEAR.begin] AND [BIRTH_YEAR.end]
group by i_item_id, c_birth_year),
 ws_items as
 (select i_item_id item_id
      ,c_birth_year birth_year
        ,sum(ws_ext_sales_price) ws_item_rev
  from web_sales
      ,item
      ,date_dim
      ,customer
 where ws_item_sk = i_item_sk
  and  d_date in (select d_date
                  from date_dim
                  where d_month_seq = (select d_month_seq
                                     from date_dim
                                     where d_date = '[SALES_DATE]'))
  and ws_sold_date_sk   = d_date_sk
  and ws_list_price between [PRICE.begin] and [PRICE.end]
  and i_manager_id BETWEEN [MANAGER.begin] and [MANAGER.end]
  and ws_bill_customer_sk = c_customer_sk
  and c_birth_year BETWEEN [BIRTH_YEAR.begin] AND [BIRTH_YEAR.end]
group by i_item_id, c_birth_year)
 [_LIMITA] select [_LIMITB] ss_items.item_id, ss_items.birth_year
       ,ss_item_rev
       ,ss_item_rev/((ss_item_rev+cs_item_rev+ws_item_rev)/3) * 100 ss_dev
       ,cs_item_rev
       ,cs_item_rev/((ss_item_rev+cs_item_rev+ws_item_rev)/3) * 100 cs_dev
       ,ws_item_rev
       ,ws_item_rev/((ss_item_rev+cs_item_rev+ws_item_rev)/3) * 100 ws_dev
       ,(ss_item_rev+cs_item_rev+ws_item_rev)/3 average
 from ss_items,cs_items,ws_items
 where ss_items.item_id=cs_items.item_id
   and ss_items.item_id=ws_items.item_id
   and ss_items.birth_year = cs_items.birth_year
   and ss_items.birth_year = ws_items.birth_year
   and ss_item_rev between 0.9 * cs_item_rev and 1.1 * cs_item_rev
   and ss_item_rev between 0.9 * ws_item_rev and 1.1 * ws_item_rev
   and cs_item_rev between 0.9 * ss_item_rev and 1.1 * ss_item_rev
   and cs_item_rev between 0.9 * ws_item_rev and 1.1 * ws_item_rev
   and ws_item_rev between 0.9 * ss_item_rev and 1.1 * ss_item_rev
   and ws_item_rev between 0.9 * cs_item_rev and 1.1 * cs_item_rev
 order by item_id, birth_year
         ,ss_item_rev
 [_LIMITC];
