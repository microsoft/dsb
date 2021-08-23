import simplejson as json
import shutil
import os
import subprocess

def load_json(filename):
	with open(filename, 'r') as f:
		data = json.load(f)
		return data

def get_query_template_files(dir, filenames):
	if os.path.isfile(dir):
		basename = os.path.basename(dir)
		if basename.startswith('query') and basename.endswith('.tpl') and (filenames == [] or basename in filenames):
			return [dir]
		return []
	else:
		result = []
		for file in os.listdir(dir):
			result.extend(get_query_template_files(os.path.join(dir, file), filenames))
		return result

def gen_gaussian_dist(exec_dir, options):
	exec_path = os.path.join(exec_dir, 'distcomp.exe')
	cmd = [exec_path, '/i', 'tpcds.dst', '/o', 'tpcds.idx', '/param_dist', 'normal', '/verbose']
	if 'param_sigma' in options:
		cmd.append('/param_sigma')
		cmd.append(str(options['param_sigma']))
	if 'param_center' in options:
		cmd.append('/param_center')
		cmd.append(str(options['param_center']))
	if 'rngseed' in options and options['rngseed'] is not None:
		cmd.append('/rngseed')
		cmd.append(str(options['rngseed']))
	print(' '.join(cmd))
	subprocess.run(cmd, shell=True, cwd = exec_dir)

def generate_queries(exec_dir, output_dir, tmp_dir, template_filename, dialect, options):
	print('generate queries for template ' + template_filename + ' to ' + output_dir)
	print('workload config:', options)

	if not os.path.exists(output_dir):
		os.makedirs(output_dir)
	query_name = os.path.splitext(os.path.basename(template_filename))[0]
	query_dir = os.path.join(output_dir, query_name)
	if not os.path.exists(query_dir):
		os.makedirs(query_dir)

	exec_path = os.path.join(exec_dir, 'dsqgen.exe')
	cmd = [exec_path, '/output_dir', tmp_dir, '/streams', str(options['instance_count']),
			'/directory', os.path.dirname(template_filename),
			'/template', os.path.basename(template_filename), '/dialect', dialect]
	if 'param_dist' in options:
		cmd.append('/param_dist')
		cmd.append(options['param_dist'])
	if 'rngseed' in options:
		cmd.append('/rngseed')
		cmd.append(str(options['rngseed']))
	print(' '.join(cmd))
	subprocess.run(cmd, shell=True, cwd = exec_dir)

	# Rename the query instance files.
	for i in range(options['instance_count']):
		shutil.copy(os.path.join(tmp_dir, 'query_' + str(i) + '.sql'),
				os.path.join(query_dir, query_name + '_' + str(i) + '.sql'))


def generate_workload(workload_config):
	output_dir = workload_config['output_dir']
	if not os.path.exists(output_dir):
		os.makedirs(output_dir)

	tmp_dir = os.path.join(output_dir, 'tmp')
	if not os.path.exists(tmp_dir):
		os.makedirs(tmp_dir)

	exec_dir = workload_config['binary_dir']
	for workload in workload_config['workload']:
		query_template_files = get_query_template_files(workload_config['query_template_root_dir'],
				workload['query_template_names'])

		# recompile distribution files if necessary
		if 'param_dist' in workload and workload['param_dist'] == 'normal':
			gen_gaussian_dist(exec_dir, workload)

		# save the weight file
		shutil.copyfile(os.path.join(exec_dir, 'tpcds.idx'),
			os.path.join(output_dir, 'tpcds_' + workload['id'] + '.idx'))

		dir = os.path.join(output_dir, workload['id'])
		for query_template_file in query_template_files:
			generate_queries(exec_dir, dir, tmp_dir, query_template_file,
										workload_config['dialect'], workload)

workload_config_file = r'D:\scripts\workload_config.json'
workload_config = load_json(workload_config_file)
generate_workload(workload_config)
