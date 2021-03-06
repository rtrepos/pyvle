#ifndef PYVLE_PYVLE_HPP
#define PYVLE_PYVLE_HPP

#include "VleBinding.hpp"
//#include <pybind11/pybind11.h>
//#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
//#include <numpy/ndarraytypes.h>
//#include <Python.h>

#include <vle/value/Table.hpp>
#include <vle/value/XML.hpp>

#include "pyvle_convert.hpp"


namespace pyvle {

void
__compile_test_port()
{
    auto ctx = vle::utils::make_context();
    std::ostringstream log, err;
    try {
        // homedir is set before calling this method
        // current dir contains tert_port pkg
        vle::utils::Package pack(ctx, "test_port");
        pack.configure();
        pack.wait(log, err);
        if (pack.isSuccess()) {
            pack.build();
            pack.wait(log, err);
            if (pack.isSuccess()) {
                pack.install();
                pack.wait(log, err);
                if (not pack.isSuccess()) {
                    std::cout << "Error while installing test_port\n";
                }
            } else {
                std::cout << "Error while building test_port\n";
            }
        } else {
            std::cout << "Error while configuring test_port\n";
        }
    } catch (const std::exception& e) {
        std::cout << "Error while compiling test_port: %s\n", e.what();
    }
}


struct Vle
{
    Vle() :
        mbinding()
    {
    }
    Vle(const std::string& filename):
        mbinding(std::make_shared<VleBinding>(filename))
    {
    }
    Vle(const std::string& filename, const std::string& pkg):
        mbinding(std::make_shared<VleBinding>(filename, pkg))
    {
    }
    std::shared_ptr<VleBinding> mbinding;
};

/////////////////
//static functions
/////////////////

VleValue
packages_list()
{
    VleValue ret;
    ret.set(VleBinding::packages_list().release());
    return ret;
}

VleValue
package_content(const std::string& pkgname)
{
    VleValue ret;
    ret.set(VleBinding::package_content(pkgname).release());
    return ret;
}

/////////////////
//basic functions
/////////////////

int
save(Vle vleObj, const std::string& filename)
{
    return vleObj.mbinding->save(filename);
}

VleValue
get_log_level(Vle vleObj)
{
    VleValue ret;
    ret.set(vleObj.mbinding->get_log_level().release());
    return ret;
}

void
set_log_level(Vle vleObj, int level)
{
    vleObj.mbinding->set_log_level(level);
}

VleValue
get_atomic_models(Vle vleObj)
{
    VleValue ret;
    ret.set(vleObj.mbinding->get_atomic_models().release());
    return ret;
}


VleValue
get_conditions(Vle vleObj)
{
    VleValue ret;
    ret.set(vleObj.mbinding->get_conditions().release());
    return ret;
}

int
add_condition(Vle vleObj, const std::string& conditionname)
{
    return vleObj.mbinding->add_condition(conditionname);
}

int
del_condition(Vle vleObj, const std::string& conditionname)
{
    return vleObj.mbinding->del_condition(conditionname);
}

VleValue
get_attached_conditions(Vle vleObj, const std::string& atomicpath)
{
    VleValue ret;
    ret.set(vleObj.mbinding->get_attached_conditions(atomicpath).release());
    return ret;
}

int
attach_condition(Vle vleObj, const std::string& atomicpath,
                 const std::string& conditionname)
{
    return vleObj.mbinding->attach_condition(atomicpath,conditionname);
}

int
detach_condition(Vle vleObj, const std::string& atomicpath,
                 const std::string& conditionname)
{
    return vleObj.mbinding->detach_condition(atomicpath, conditionname);
}

VleValue
get_condition_ports(Vle vleObj, const std::string& conditionname)
{
    VleValue ret;
    ret.set(vleObj.mbinding->get_condition_ports(conditionname).release());
    return ret;
}

int
add_condition_port(Vle vleObj, const std::string& conditionname,
              const std::string& portname)
{
    return vleObj.mbinding->add_condition_port(conditionname, portname);
}

int
del_condition_port(Vle vleObj,  const std::string& conditionname,
                 const std::string& portname)
{
    return vleObj.mbinding->del_condition_port(conditionname, portname);
}

VleValue
get_condition_port_value(Vle vleObj,  const std::string& conditionname,
                      const std::string& portname)
{
    VleValue ret;
    ret.set(vleObj.mbinding->get_condition_port_value(
            conditionname, portname).release());
    return ret;
}

int
set_condition_port_value(Vle vleObj,  const std::string& conditionname,
        const std::string& portname,
        VleValue val)
{
    return vleObj.mbinding->set_condition_port_value(conditionname,
            portname, std::unique_ptr<vv::Value>(val.get_vle_value()));

}

VleValue
get_observables(Vle vleObj)
{
    VleValue ret;
    ret.set(vleObj.mbinding->get_observables().release());
    return ret;
}

VleValue
get_observable_ports(Vle vleObj,  const std::string& obsName)
{
    VleValue ret;
    ret.set(vleObj.mbinding->get_observable_ports(obsName).release());
    return ret;
}

int
add_observable_port(Vle vleObj,  const std::string& obsName,
                    const std::string& portName)
{
    return vleObj.mbinding->add_observable_port(obsName, portName);
}

int
del_observable_port(Vle vleObj, const std::string& obsName,
                       const std::string& portName)
{
    return vleObj.mbinding->del_observable_port(obsName, portName);
}

int
attach_view(Vle vleObj,  const std::string& view, const std::string& obsName,
            const std::string& portName)
{
    return vleObj.mbinding->attach_view(view, obsName, portName);
}

int
detach_view(Vle vleObj, const std::string& view, const std::string& obsName,
            const std::string& portName)
{
    return vleObj.mbinding->detach_view(view, obsName, portName);
}

VleValue
get_attached_views(Vle vleObj,  const std::string& obsName,
        const std::string& portName)
{
    VleValue ret;
    ret.set(vleObj.mbinding->get_attached_views(obsName, portName).release());
    return ret;
}

VleValue
get_views(Vle vleObj)
{
    VleValue ret;
    ret.set(vleObj.mbinding->get_views().release());
    return ret;
}

int
add_view(Vle vleObj,  const std::string& view)
{
    return vleObj.mbinding->add_view(view);
}

int
del_view(Vle vleObj,  const std::string& view)
{
    return vleObj.mbinding->del_view(view);
}

VleValue
get_view_config(Vle vleObj,  const std::string& viewname)
{
    VleValue ret;
    ret.set(vleObj.mbinding->get_view_config(viewname).release());
    return ret;
}

int
set_view_config(Vle vleObj,  const std::string& viewname,
                const std::string& config)
{
    return vleObj.mbinding->set_view_config(viewname, config);
}

VleValue
get_view_plugin(Vle vleObj,  const std::string& viewname)
{
    VleValue ret;
    ret.set(vleObj.mbinding->get_view_plugin(viewname).release());
    return ret;
}

int
set_view_plugin(Vle vleObj,  const std::string& viewname,
        const std::string& pluginname, const std::string& package)
{
    return vleObj.mbinding->set_view_plugin(viewname, pluginname, package);
}

VleValue
available_outputs(Vle vleObj)
{
    VleValue ret;
    ret.set(vleObj.mbinding->available_outputs().release());
    return ret;
}

VleValue
run(Vle vleObj)
{
    VleValue ret;
    ret.set(vleObj.mbinding->run().release());
    return ret;
}

////////////////////////
//manager functions
////////////////////////

void
manager_clear(Vle vleObj)
{
    vleObj.mbinding->manager_clear();
}

VleValue
manager_get_config(Vle vleObj)
{
    VleValue ret;
    ret.set(vleObj.mbinding->manager_get_config().release());
    return ret;
}

void
manager_set_config(Vle vleObj, const std::string& parallel_option,
        int nb_slots, int simulation_spawn,  int rm_MPI_files,
        int generate_MPI_host, const std::string&  working_dir)
{

    vleObj.mbinding->manager_set_config(parallel_option, nb_slots,
            simulation_spawn, rm_MPI_files, generate_MPI_host, working_dir);
}

////////////////////////
//plan functions
////////////////////////

void
plan_clear(Vle vleObj)
{
    vleObj.mbinding->plan_clear();
}

VleValue
plan_get(Vle vleObj)
{
    VleValue ret;
    ret.set(vleObj.mbinding->plan_get().release());
    return ret;
}

void
plan_define(Vle vleObj,  const std::string& cond, const std::string& port,
        bool addORremove)
{
    vleObj.mbinding->plan_define(cond, port, addORremove);
}

void
plan_input(Vle vleObj, const std::string& cond, const std::string& port,
        VleValue val)
{
    vleObj.mbinding->plan_input(cond, port,
            std::unique_ptr<vv::Value>(val.get_vle_value()));
}

void
plan_propagate(Vle vleObj,  const std::string& cond, const std::string& port,
        VleValue val)
{
    vleObj.mbinding->plan_propagate(cond, port,
            std::unique_ptr<vv::Value>(val.get_vle_value()));
}

void
plan_replicate(Vle vleObj,  const std::string& cond, const std::string& port,
        VleValue val)
{
    vleObj.mbinding->plan_replicate(cond, port,
            std::unique_ptr<vv::Value>(val.get_vle_value()));
}


int
plan_output(Vle vleObj,  const std::string& id, const std::string& path,
        const std::string& integration,
        const std::string& aggregation_replicate,
        const std::string& aggregation_input,
        VleValue obs_times,
        VleValue obs_values,
        double replicate_quantile)
{
    return vleObj.mbinding->plan_output(id, path, integration,
            aggregation_replicate, aggregation_input,
            std::unique_ptr<vv::Value>(obs_times.get_vle_value()),
            std::unique_ptr<vv::Value>(obs_values.get_vle_value()),
            replicate_quantile);
}

VleValue
plan_run(Vle vleObj)
{
    VleValue ret;
    ret.set(vleObj.mbinding->plan_run().release());
    return ret;
}

Vle
plan_embedded(Vle vleObj, int input, int replicate)
{
    Vle ret;
    ret.mbinding.reset(vleObj.mbinding->plan_embedded(
            input, replicate).release());
    return ret;
}

////////////////////////
//experiment functions
////////////////////////

VleValue
experiment_run(Vle vleObjExpe, Vle vleObjMod, VleValue experiment_settings)
{
    VleValue ret;
    ret.set(vleObjExpe.mbinding->experiment_run(
            *vleObjMod.mbinding,
             std::unique_ptr<vv::Value>(
                     experiment_settings.get_vle_value())).release());
    return ret;
}


}// end namespace pyvle

#endif
