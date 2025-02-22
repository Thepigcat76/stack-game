#pragma once

#define REGISTRY_LEN 1000

#define create_registry(type) struct _registry_##type { type *elems; unsigned long len; };

#define Registry(type) struct _registry_##type

#define registry_init(type, registry) type elems[REGISTRY_LEN]; registry = (Registry(type)) {.elems = elems, .len = 0}

#define registry_add(registry, elem) registry.elems[registry.len++] = elem

#define registry_get(registry, index) registry.elems[index]
