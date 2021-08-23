# Project

This directory contains the source code and helper scripts to generate data and query workloads for DS++ benchmark.

Disclaimer: The DS++ benchmark is adapted from the TPC-DS benchmark v2.11.0rc2. Its performance metrics and the evaluation result based on DS++ will not be comparable with these based on TPC-DS benchmark.

===========================

Compile the code
- The code can be compiled based on the instructions in ./code/v2.11.0rc2/tools/How_To_Guide-DS-V2.0.0.docx.

===========================

Data generation
- The data can be generated based on the instructions in ./code/v2.11.0rc2/tools/How_To_Guide-DS-V2.0.0.docx.
- Because the DS++ benchmark includes correlation between tables, the tables must be generated following a partial order. * We strongly suggest that the users generate ALL the tables when populating the data files *. Generating / repopulating an individual table file can result in incorrect correlation between tables.
- Sample script to generate data files: ./scripts/generate_dspp_db_files.py
- Sample script to load the data files to Microsoft SQL Server: ./scripts/load_data_sqlserver.py
- Sample script to load the data files to Postgres: ./scripts/load_data_pg.py

===========================

Physical configuration
- We provide a sample physical configuration of 56 B+ tree indexes for the database. The physical configuration is produced by the Database Tuning Advisor (DTA) from Microsoft SQL Server based on a 100GB DS++ database. This physical configuration is only for demonstration purpose. We suggest the users to produce their own physical configuration based on the database instance and the query workloads.
- The SQL file to create the indexes for Microsoft SQL Server: ./scripts/dspp_index_sqlserver.sql
- THe SQL file to create the indexes for Postgres: ./scripts/dspp_index_pg.sql

===========================

Query templates
- The query templates are adapted from the TPC-DS benchmark with three new queries (100, 101, 102). For the query templates adapted from TPC-DS benchmark, we keep the original query ID of the template.
- The queries are divided into two groups: agg_queries (i.e., single block queries) and multi-block queries.
- The DS++ benchmark also includes a set of single-block SPJ queries that are derived from the query templates for evaluating techniques with limited capabilities.
- The query templates for Microsoft SQL Server dialect: ./query_templates_sqlserver
- The query templates for Postgres dialect: ./query_templates_pg

===========================

Query generation
- The query workloads can be generated with workload configurations.
- Sample script to generate workloads: ./scripts/generate_workload.py
	- * This script MUST be executed from the path of the binary of the query generation tool, e.g., D:\code\v2.11.0rc2\tools. *
- Sample workload configuration: ./scripts/workload_config.json
- As part of the query generation, our tool will output a tpcds.idx file, which stores the probability distributions of the values in each domain in a workload.

Workload configuration parameters
- A workload configuration is a JSON object that consists of a sequence of workload distributions
- Each workload configuration has the following meta parameters:
	- output_dir: The path to store the output query files
	- binary_dir: The path of the binary of the query generation tool
	- query_template_root_dir: The root directory of the query templates. It will be traversed recursively
	- dialect: "sqlserver" or "postgres"
	- workload: an array of workload distributions
- Each workload distribution has the following parameters:
	- id: The id of the workload distribution
	- query_template_names: The names of the query template to be included in this workload distribution. An empty list means including all the query templates
	- instance_count: The number of query instances per query template
	- param_dist: "normal" or "default", where "normal" means using Gaussian distribution.
	- param_sigma: a positive numerical value. This is the variance of the Gaussian distribution (if applicable)
	- param_center: a numerical value between [-0.5, 0.5]. This is the shift of the center of the Gaussian distribution (if applicable)
	- rngseed: an integer. This is used for generating the permutation of the values in each domain. The same rngseed can be used to fix the parameter value permutation.

=========================

Test
- The code and scripts for data generation and query generation are tested under Windows Server 2019.
- The query templates are tested under Microsoft SQL Server 2019 and Postgres V13.


## Contributing

This project welcomes contributions and suggestions.  Most contributions require you to agree to a
Contributor License Agreement (CLA) declaring that you have the right to, and actually do, grant us
the rights to use your contribution. For details, visit https://cla.opensource.microsoft.com.

When you submit a pull request, a CLA bot will automatically determine whether you need to provide
a CLA and decorate the PR appropriately (e.g., status check, comment). Simply follow the instructions
provided by the bot. You will only need to do this once across all repos using our CLA.

This project has adopted the [Microsoft Open Source Code of Conduct](https://opensource.microsoft.com/codeofconduct/).
For more information see the [Code of Conduct FAQ](https://opensource.microsoft.com/codeofconduct/faq/) or
contact [opencode@microsoft.com](mailto:opencode@microsoft.com) with any additional questions or comments.

## Trademarks

This project may contain trademarks or logos for projects, products, or services. Authorized use of Microsoft
trademarks or logos is subject to and must follow
[Microsoft's Trademark & Brand Guidelines](https://www.microsoft.com/en-us/legal/intellectualproperty/trademarks/usage/general).
Use of Microsoft trademarks or logos in modified versions of this project must not cause confusion or imply Microsoft sponsorship.
Any use of third-party trademarks or logos are subject to those third-party's policies.
